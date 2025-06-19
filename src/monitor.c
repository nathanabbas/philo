/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:01:05 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/19 14:01:06 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool all_fed(t_rules *r)
{
	int i = -1;
	int full = 0;

	if (r->must_eat < 0)
		return false;

	while (++i < r->n_philo)
	{
		pthread_mutex_lock(&r->philos[i].lock);
		if (r->philos[i].meals >= r->must_eat)
			full++;
		pthread_mutex_unlock(&r->philos[i].lock);
	}
	return (full == r->n_philo);
}

static bool check_death(t_rules *r, int i)
{
	long now, last_meal;
	bool first;

	pthread_mutex_lock(&r->philos[i].lock);
	last_meal = r->philos[i].last_meal;
	pthread_mutex_unlock(&r->philos[i].lock);

	now = get_time_ms();
	if (now - last_meal >= r->t_die)
	{
		pthread_mutex_lock(&r->sim_lock);
		first = !r->stop;
		r->stop = true;
		pthread_mutex_unlock(&r->sim_lock);

		if (first)
			log_state(&r->philos[i], "died", true);
		return true;
	}
	return false;
}

void monitor(t_rules *r)
{
	int i;

	while (1)
	{
		pthread_mutex_lock(&r->sim_lock);
		if (r->stop)
		{
			pthread_mutex_unlock(&r->sim_lock);
			break;
		}
		pthread_mutex_unlock(&r->sim_lock);

		i = -1;
		while (++i < r->n_philo)
			if (check_death(r, i))
				return ;

		if (all_fed(r))
		{
			pthread_mutex_lock(&r->sim_lock);
			r->stop = true;
			pthread_mutex_unlock(&r->sim_lock);
			return;
		}
		usleep(100);
	}
}
