/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:25:00 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/22 15:07:29 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* ───────────── fork helpers ────────────────────────────────────────────── */

static void	take_one(t_philo *p)
{
	pthread_mutex_lock(p->left);
	log_state(p, "has taken a fork");
}

static void	take_two(t_philo *p)
{
	waiter_take(p->rules);
	pthread_mutex_lock(p->left);
	log_state(p, "has taken a fork");
	pthread_mutex_lock(p->right);
	log_state(p, "has taken a fork");
}

static void	release_two(t_philo *p)
{
	pthread_mutex_unlock(p->left);
	pthread_mutex_unlock(p->right);
	waiter_give(p->rules);
}

/* ───────────── eat / routine ───────────────────────────────────────────── */

static void	do_eat(t_philo *p)
{
	pthread_mutex_lock(&p->rules->meal_lock);
	p->last_meal = timestamp_ms();
	pthread_mutex_unlock(&p->rules->meal_lock);
	log_state(p, "is eating");
	ft_usleep(p->rules, p->rules->t_eat);
	release_two(p);
	p->meals_eaten++;
}

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	/* single philosopher: grab one fork, wait, let monitor print death */
	if (p->rules->n_philo == 1)
	{
		take_one(p);
		ft_usleep(p->rules, p->rules->t_die);
		pthread_mutex_unlock(p->left);
		return (NULL);
	}
	if (p->id % 2 == 0)
		usleep(150);
	while (!is_dead(p->rules) && !all_fed(p->rules))
{
	take_two(p);
	do_eat(p);

	log_state(p, "is sleeping");
	ft_usleep(p->rules, p->rules->t_sleep);

	log_state(p, "is thinking");
	if (p->rules->n_philo % 2 == 1)
		ft_usleep(p->rules, p->rules->t_eat);
}

	return (NULL);
}
