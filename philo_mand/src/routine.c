/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:27:36 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/21 13:02:00 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* --------------------------- exit helpers --------------------------------- */

static bool	done_eating(t_philo *p)
{
	bool	done;

	pthread_mutex_lock(&p->lock);
	done = (p->rules->must_eat > -1 && p->meals >= p->rules->must_eat);
	pthread_mutex_unlock(&p->lock);
	return (done);
}

static bool	should_stop(t_philo *p)
{
	bool	stop;

	pthread_mutex_lock(&p->rules->sim_lock);
	stop = p->rules->stop;
	pthread_mutex_unlock(&p->rules->sim_lock);
	return (stop);
}

/* --------------------------- solo case ------------------------------------ */

static void	*solo_routine(t_philo *p)
{
	pthread_mutex_lock(p->l_fork);
	pthread_mutex_lock(&p->rules->print);
	printf("0 %d has taken a fork\n", p->id);
	pthread_mutex_unlock(&p->rules->print);
	ft_usleep(p->rules->t_die);
	pthread_mutex_lock(&p->rules->sim_lock);
	p->rules->stop = true;
	pthread_mutex_unlock(&p->rules->sim_lock);
	pthread_mutex_lock(&p->rules->print);
	printf("%d %d died\n", p->rules->t_die, p->id);
	pthread_mutex_unlock(&p->rules->print);
	pthread_mutex_unlock(p->l_fork);
	return (NULL);
}

/* --------------------------- worker loop ---------------------------------- */

static void	philo_loop(t_philo *p)
{
	while (!should_stop(p))
	{
		eat(p);
		if (done_eating(p))
			break ;
		log_state(p, "is sleeping", false);
		smart_sleep(p->rules->t_sleep, p->rules);
		think(p);
	}
}

/* --------------------------- public entry --------------------------------- */

void	*routine(void *arg)
{
	t_philo	*p;

	p = arg;
	if (p->rules->n_philo == 1)
		return (solo_routine(p));
	if (p->id % 2 == 0)
		usleep(1000);
	philo_loop(p);
	return (NULL);
}
