/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:58:51 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/15 10:22:51 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_rules	*r;
	int		i;
	long	now;

	r = (t_rules *)arg;
	while (!all_fed(r) && !is_dead(r))
	{
		i = 0;
		while (i < r->n_philo)
		{
			/* lock just to read last_meal */
			pthread_mutex_lock(&r->meal_lock);
			now = timestamp_ms();
			if (now - r->philos[i].last_meal >= r->t_die)
			{
				/* mark death */
				r->someone_died = 1;
				pthread_mutex_unlock(&r->meal_lock);

				/* print once, safely */
				pthread_mutex_lock(&r->print_lock);
				printf("%ld %d died\n",
					now - r->start_ts,
					r->philos[i].id);
				pthread_mutex_unlock(&r->print_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&r->meal_lock);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
