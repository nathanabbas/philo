/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:59:00 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/15 09:59:01 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_mutexes(t_rules *r)
{
	int	i;

	pthread_mutex_destroy(&r->print_lock);
	pthread_mutex_destroy(&r->meal_lock);
	i = 0;
	while (i < r->n_philo)
	{
		pthread_mutex_destroy(&r->forks[i]);
		i++;
	}
}

void	clean_exit(t_rules *r, int code)
{
	int	i;

	i = 0;
	while (i < r->n_philo)
	{
		pthread_join(r->philos[i].thread, NULL);
		i++;
	}
	pthread_join(r->monitor, NULL);
	destroy_mutexes(r);
	free(r->forks);
	free(r->philos);
	exit(code);
}
