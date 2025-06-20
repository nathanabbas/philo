/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:27:36 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/20 16:08:18 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *p)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = p->l_fork;
	second = p->r_fork;
	if (p->id % 2 == 0)
	{
		first = p->r_fork;
		second = p->l_fork;
	}
	pthread_mutex_lock(first);
	log_state(p, "has taken a fork", false);
	pthread_mutex_lock(second);
	log_state(p, "has taken a fork", false);
}

static void	smart_sleep(long duration, t_rules *rules)
{
	long	start;

	start = get_time_ms();
	while (get_time_ms() - start < duration)
	{
		pthread_mutex_lock(&rules->sim_lock);
		if (rules->stop)
		{
			pthread_mutex_unlock(&rules->sim_lock);
			break ;
		}
		pthread_mutex_unlock(&rules->sim_lock);
		usleep(100);
	}
}

static void	eat(t_philo *p)
{
	take_forks(p);
	pthread_mutex_lock(&p->lock);
	p->last_meal = get_time_ms();
	pthread_mutex_unlock(&p->lock);
	log_state(p, "is eating", false);
	ft_usleep(p->rules->t_eat);
	pthread_mutex_lock(&p->lock);
	p->meals++;
	pthread_mutex_unlock(&p->lock);
	pthread_mutex_unlock(p->r_fork);
	pthread_mutex_unlock(p->l_fork);
}

static void	*solo_routine(t_philo *p)
{
	pthread_mutex_lock(p->l_fork);
	pthread_mutex_lock(&p->rules->print);
	printf("0 %d has taken a fork\n", p->id);
	pthread_mutex_unlock(&p->rules->print);
	ft_usleep(p->rules->t_die);
	pthread_mutex_lock(&p->rules->sim_lock);
	p->rules->stop = true;
	pthread_mutex_unlock(&p->rules->sim_lock);
	pthread_mutex_lock(&p->rules->print);
	printf("%d %d died\n", p->rules->t_die, p->id);
	pthread_mutex_unlock(&p->rules->print);
	pthread_mutex_unlock(p->l_fork);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = arg;
	if (p->rules->n_philo == 1)
		return (solo_routine(p));
	if (p->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&p->rules->sim_lock);
		if (p->rules->stop)
		{
			pthread_mutex_unlock(&p->rules->sim_lock);
			break ;
		}
		pthread_mutex_unlock(&p->rules->sim_lock);
		eat(p);
		log_state(p, "is sleeping", false);
		smart_sleep(p->rules->t_sleep, p->rules);
		log_state(p, "is thinking", false);
	}
	return (NULL);
}
