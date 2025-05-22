/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:58:51 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/22 15:36:37 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_rules *rules, int i)
{
	long	now;

	pthread_mutex_lock(&rules->meal_lock);
	now = timestamp_ms();
	if (now - rules->philos[i].last_meal >= rules->t_die)
	{
		rules->someone_died = 1;
		pthread_mutex_unlock(&rules->meal_lock);
		pthread_mutex_lock(&rules->print_lock);
		printf("%ld %d died\n",
			now - rules->start_ts,
			rules->philos[i].id);
		pthread_mutex_unlock(&rules->print_lock);
		return (1);
	}
	pthread_mutex_unlock(&rules->meal_lock);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_rules	*rules;
	int		i;

	rules = (t_rules *)arg;
	while (!all_fed(rules) && !is_dead(rules))
	{
		i = 0;
		while (i < rules->n_philo)
		{
			if (check_death(rules, i))
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
