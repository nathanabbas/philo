/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:05:00 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/22 15:34:09 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->n_philo)
	{
		if (i % 2 == 0)
		{
			rules->philos[i].left = \
&rules->forks[(i + 1) % rules->n_philo];
			rules->philos[i].right = &rules->forks[i];
		}
		else
		{
			rules->philos[i].left = &rules->forks[i];
			rules->philos[i].right = \
&rules->forks[(i + 1) % rules->n_philo];
		}
		i++;
	}
}

static int	create_mutexes(t_rules *rules)
{
	int	i;

	if (pthread_mutex_init(&rules->print_lock, NULL))
		return (1);
	if (pthread_mutex_init(&rules->meal_lock, NULL))
		return (1);
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->n_philo);
	if (!rules->forks)
		return (1);
	i = 0;
	while (i < rules->n_philo)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

int	init_simulation(t_rules *rules)
{
	int	i;

	if (create_mutexes(rules))
		return (1);
	rules->philos = malloc(sizeof(t_philo) * rules->n_philo);
	if (!rules->philos)
		return (1);
	i = 0;
	while (i < rules->n_philo)
	{
		rules->philos[i].id = i + 1;
		rules->philos[i].meals_eaten = 0;
		rules->philos[i].last_meal = 0;
		rules->philos[i].rules = rules;
		i++;
	}
	assign_forks(rules);
	waiter_init(rules, rules->n_philo / 2);
	return (0);
}
