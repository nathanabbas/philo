/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:38:29 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/22 15:38:37 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*single_philo(t_philo *p)
{
	take_one(p);
	ft_usleep(p->rules, p->rules->t_die);
	pthread_mutex_unlock(p->left);
	return (NULL);
}

static void	philo_cycle(t_philo *p)
{
	take_two(p);
	do_eat(p);
	log_state(p, "is sleeping");
	ft_usleep(p->rules, p->rules->t_sleep);
	log_state(p, "is thinking");
	if (p->rules->n_philo % 2 == 1)
		ft_usleep(p->rules, p->rules->t_eat);
}

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->rules->n_philo == 1)
		return (single_philo(p));
	if (p->id % 2 == 0)
		usleep(150);
	while (!is_dead(p->rules) && !all_fed(p->rules))
		philo_cycle(p);
	return (NULL);
}
