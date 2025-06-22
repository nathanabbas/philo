/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:01:25 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/22 16:14:04 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	done_eating(t_philo *p)
{
	int	done;

	sem_wait(p->lock);
	done = (p->rules->must_eat > -1 && p->meals >= p->rules->must_eat);
	sem_post(p->lock);
	return (done);
}

static void	solo_philo(t_philo *p)
{
	log_state(p, "has taken a fork", 0);
	ft_usleep(p->rules->t_die);
	log_state(p, "died", 1);
	exit(1);
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->rules->n_philo == 1)
		solo_philo(p);
	if (pthread_create(&p->mon, 0, monitor, p) != 0)
		exit(1);
	if (p->id % 2 == 0)
		usleep(2000);
	while (1)
	{
		eat(p);
		if (done_eating(p))
			exit(0);
		sleep_philo(p);
		think(p);
	}
	return (0);
}
