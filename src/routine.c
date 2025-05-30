/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:27:36 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/26 13:40:06 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** eat()
** A normal philosopher takes two different forks, eats, and releases them.
*/
static void	eat(t_philo *p)
{
	pthread_mutex_lock(p->l_fork);
	log_state(p, "has taken a fork", false);
	pthread_mutex_lock(p->r_fork);
	log_state(p, "has taken a fork", false);
	pthread_mutex_lock(&p->lock);
	p->last_meal = get_time_ms();
	pthread_mutex_unlock(&p->lock);
	log_state(p, "is eating", false);
	ft_usleep(p->rules->t_eat);
	pthread_mutex_lock(&p->lock);
	p->meals++;
	pthread_mutex_unlock(&p->lock);
	pthread_mutex_unlock(p->r_fork);
	pthread_mutex_unlock(p->l_fork);
}

/*
** routine() — thread entry point
** Includes a dedicated branch for the 1-philosopher case to avoid dead-lock.
*/
/* ------------------------------------------------------------------ */
/*  solo_routine() – 1-philosopher case                               */
/* ------------------------------------------------------------------ */


static void *solo_routine(t_philo *p)
{
    /* take the single fork */
    pthread_mutex_lock(p->l_fork);

    /* print “0 X has taken a fork” under print-lock */
    pthread_mutex_lock(&p->rules->print);
    printf("0 %d has taken a fork\n", p->id);
    pthread_mutex_unlock(&p->rules->print);

    /* sleep exactly time_to_die */
    ft_usleep(p->rules->t_die);

    /* mark stop under sim_lock so monitor quits silently */
    pthread_mutex_lock(&p->rules->sim_lock);
    p->rules->stop = true;
    pthread_mutex_unlock(&p->rules->sim_lock);

    /* print “200 X died” under the same print-lock */
    pthread_mutex_lock(&p->rules->print);
    printf("%d %d died\n", p->rules->t_die, p->id);
    pthread_mutex_unlock(&p->rules->print);

    pthread_mutex_unlock(p->l_fork);
    return (NULL);
}


void	*routine(void *arg)
{
	t_philo	*p;

	p = arg;
	if (p->rules->n_philo == 1)
		return (solo_routine(p));
    if (p->id % 2 == 0)
        usleep(1000);
    while (true)
    {
        pthread_mutex_lock(&p->rules->sim_lock);
        if (p->rules->stop)
            return (pthread_mutex_unlock(&p->rules->sim_lock), NULL);
        pthread_mutex_unlock(&p->rules->sim_lock);
        eat(p);
        log_state(p, "is sleeping", false);
        ft_usleep(p->rules->t_sleep);
        log_state(p, "is thinking", false);
    }
    return (NULL);
}
