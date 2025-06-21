/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:44:01 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/26 12:44:06 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_rules *r)
{
	int	i;

	i = -1;
	while (++i < r->n_philo)
	{
		pthread_mutex_destroy(&r->forks[i]);
		pthread_mutex_destroy(&r->philos[i].lock);
	}
	pthread_mutex_destroy(&r->print);
	pthread_mutex_destroy(&r->sim_lock);
	free(r->forks);
	free(r->philos);
}
