/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:00:25 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/22 17:00:28 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_two(t_philo *p)
{
	waiter_take(p->rules);
	pthread_mutex_lock(p->left);
	log_state(p, "has taken a fork");
	pthread_mutex_lock(p->right);
	log_state(p, "has taken a fork");
}

static void	do_eat(t_philo *p)
{
	pthread_mutex_lock(&p->rules->meal_lock);
	p->last_meal = timestamp_ms();
	pthread_mutex_unlock(&p->rules->meal_lock);
	log_state(p, "is eating");
	ft_usleep(p->rules, p->rules->t_eat);
	pthread_mutex_unlock(p->left);
	pthread_mutex_unlock(p->right);
	waiter_give(p->rules);
	pthread_mutex_lock(&p->rules->meal_lock);
	p->meals_eaten++;
	pthread_mutex_unlock(&p->rules->meal_lock);
}

static void	*single_philo(t_philo *p)
{
	if (all_fed(p->rules) || is_dead(p->rules))
		return (NULL);
	pthread_mutex_lock(p->left);
	log_state(p, "has taken a fork");
	ft_usleep(p->rules, p->rules->t_die);
	pthread_mutex_unlock(p->left);
	return (NULL);
}

static void	philo_cycle(t_philo *p)
{
	if (all_fed(p->rules) || is_dead(p->rules))
		return ;
	take_two(p);
	if (all_fed(p->rules) || is_dead(p->rules))
		return ;
	do_eat(p);
	if (all_fed(p->rules) || is_dead(p->rules))
		return ;
	log_state(p, "is sleeping");
	ft_usleep(p->rules, p->rules->t_sleep);
	if (all_fed(p->rules) || is_dead(p->rules))
		return ;
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
	while (!all_fed(p->rules) && !is_dead(p->rules))
		philo_cycle(p);
	return (NULL);
}
