/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:56:36 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/24 14:07:25 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo *p = arg;
	t_rules *r = p->rules;
	int      last_meal;

	if (r->n_philo == 1)
	{
		pthread_mutex_lock(p->left);
		log_state(p, "has taken a fork");
		ft_usleep(r, r->t_die);
		pthread_mutex_unlock(p->left);
		return (NULL);
	}
	if (p->id % 2 == 1)
		usleep(100);

	while (!is_dead(r) && !all_fed(r))
	{
		/* take forks */
		pthread_mutex_lock(p->left);
		log_state(p, "has taken a fork");
		pthread_mutex_lock(p->right);
		log_state(p, "has taken a fork");

		/* eat */
		pthread_mutex_lock(&r->meal_lock);
		p->last_meal = timestamp_ms();
		pthread_mutex_unlock(&r->meal_lock);
		log_state(p, "is eating");
		ft_usleep(r, r->t_eat);

		/* update meal count */
		pthread_mutex_lock(&r->meal_lock);
		p->meals_eaten++;
		last_meal = (r->meals_target > 0 &&
		             p->meals_eaten == r->meals_target);
		if (last_meal)
			r->fed_count++;              /* NEW */
		pthread_mutex_unlock(&r->meal_lock);

		/* put forks back */
		pthread_mutex_unlock(p->left);
		pthread_mutex_unlock(p->right);

		/* if everyone is fed now, leave immediately */
		if (all_fed(r))
			break;

		/* normal sleep / think cycle */
		log_state(p, "is sleeping");
		ft_usleep(r, r->t_sleep);
		log_state(p, "is thinking");
	}
	return (NULL);
}
