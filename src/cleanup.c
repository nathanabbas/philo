/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:06:00 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/22 15:32:42 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* ─ helpers ───────────────────────────────────────────────────────────── */

static void	destroy_mutexes(t_rules *r)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&r->print_lock);
	pthread_mutex_destroy(&r->meal_lock);
	while (i < r->n_philo)
		pthread_mutex_destroy(&r->forks[i++]);
	waiter_destroy(r);
}

/* ─ public exit path ──────────────────────────────────────────────────── */

void	clean_exit(t_rules *r, int code)
{
	int	i;

	i = 0;
	while (i < r->n_philo)
		pthread_join(r->philos[i++].thread, NULL);
	pthread_join(r->monitor, NULL);
	destroy_mutexes(r);
	free(r->forks);
	free(r->philos);
	exit(code);
}
