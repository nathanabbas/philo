/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:57:21 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/30 19:41:43 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool  all_fed(t_rules *r);
static bool  check_death(t_rules *r, int idx);

/* ------------------------------------------------------------------ */
/*  helper: did everyone eat enough?                                   */
/* ------------------------------------------------------------------ */
static bool	all_fed(t_rules *r)
{
	int	i;
	int	full;

	if (r->must_eat < 0)
		return (false);
	full = 0;
	i = -1;
	while (++i < r->n_philo)
	{
		pthread_mutex_lock(&r->philos[i].lock);
		if (r->philos[i].meals >= r->must_eat)
			full++;
		pthread_mutex_unlock(&r->philos[i].lock);
	}
	return (full == r->n_philo);
}

/* ------------------------------------------------------------------ */
/*  helper: check one philosopher for death and log it once            */
/* ------------------------------------------------------------------ */
static bool	check_death(t_rules *r, int idx)
{
	long	now;
	bool	first;

	pthread_mutex_lock(&r->philos[idx].lock);
	now = get_time_ms();
	if (now - r->philos[idx].last_meal >= r->t_die)
	{
		pthread_mutex_unlock(&r->philos[idx].lock);

		pthread_mutex_lock(&r->sim_lock);
		first = !r->stop;
		r->stop = true;
		pthread_mutex_unlock(&r->sim_lock);

		if (first)
			log_state(&r->philos[idx], "died", true);
		exit(0);
	}
	pthread_mutex_unlock(&r->philos[idx].lock);
	return (false);
}



/* ------------------------------------------------------------------ */
/*  monitor thread                                                     */
/* ------------------------------------------------------------------ */
void	monitor(t_rules *r)
{
	int	i;

	while (true)
	{
		pthread_mutex_lock(&r->sim_lock);
		if (r->stop)
			exit(0);
		pthread_mutex_unlock(&r->sim_lock);
		i = -1;
		while (++i < r->n_philo)
			if (check_death(r, i))
				return ;
		if (all_fed(r))
		{
			pthread_mutex_lock(&r->sim_lock);
			r->stop = true;
			exit(0);
		}
		usleep(100);
	}
}
