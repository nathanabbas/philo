/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:40:57 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/22 16:56:24 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	think(t_philo *p)
{
	long	window;

	window = p->rules->t_die - (p->rules->t_eat + p->rules->t_sleep);
	if (window < 0)
		window = 0;
	else if (window > 600)
		window = 200;
	else
		window /= 2;
	log_state(p, "is thinking", 0);
	smart_sleep(window, p->rules);
}

void	sleep_philo(t_philo *p)
{
	log_state(p, "is sleeping", 0);
	smart_sleep(p->rules->t_sleep, p->rules);
}

void	eat(t_philo *p)
{
	sem_wait(p->rules->forks);
	log_state(p, "has taken a fork", 0);
	sem_wait(p->rules->forks);
	log_state(p, "has taken a fork", 0);
	sem_wait(p->lock);
	p->last_meal = get_time_ms();
	p->meals++;
	sem_post(p->lock);
	log_state(p, "is eating", 0);
	smart_sleep(p->rules->t_eat, p->rules);
	sem_post(p->rules->forks);
	sem_post(p->rules->forks);
}
