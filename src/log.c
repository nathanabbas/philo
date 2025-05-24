/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:08:49 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/24 14:08:50 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15                                   */
/*   Updated: 2025/05/24                                   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* ---------------------------------------------------------------- */
/*  Print state if no one died and not all fed                      */
/* ---------------------------------------------------------------- */
void	log_state(t_philo *p, const char *msg)
{
	long	now;

	now = timestamp_ms() - p->rules->start_ts;
	pthread_mutex_lock(&p->rules->print_lock);
	if (!p->rules->someone_died && !all_fed(p->rules))
		printf("%ld %d %s\n", now, p->id, msg);
	pthread_mutex_unlock(&p->rules->print_lock);
}

/* ---------------------------------------------------------------- */
/*  Check global death flag (needs locking)                          */
/* ---------------------------------------------------------------- */
int	is_dead(t_rules *r)
{
	int	status;

	pthread_mutex_lock(&r->meal_lock);
	status = r->someone_died;
	pthread_mutex_unlock(&r->meal_lock);
	return (status);
}

/* ---------------------------------------------------------------- */
/*  O(1) all-fed check using fed_count                               */
/* ---------------------------------------------------------------- */
int	all_fed(t_rules *r)
{
	if (r->meals_target < 0)
		return (0);
	pthread_mutex_lock(&r->meal_lock);
	if (r->fed_count == r->n_philo)
	{
		pthread_mutex_unlock(&r->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&r->meal_lock);
	return (0);
}

