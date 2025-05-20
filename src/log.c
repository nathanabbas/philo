/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:58:21 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/15 09:58:23 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_state(t_philo *p, char *msg)
{
	long	now;

	pthread_mutex_lock(&p->rules->print_lock);
	now = timestamp_ms() - p->rules->start_ts;
	if (!p->rules->someone_died && !all_fed(p->rules))
		printf("%ld %d %s\n", now, p->id, msg);
	pthread_mutex_unlock(&p->rules->print_lock);
}

int	is_dead(t_rules *r)
{
	int	status;

	pthread_mutex_lock(&r->meal_lock);
	status = r->someone_died;
	pthread_mutex_unlock(&r->meal_lock);
	return (status);
}

int	all_fed(t_rules *r)
{
	int	i;
	int	full;

	if (r->meals_target < 0)
		return (0);
	i = 0;
	full = 1;
	while (i < r->n_philo)
	{
		if (r->philos[i].meals_eaten < r->meals_target)
			full = 0;
		i++;
	}
	return (full);
}
