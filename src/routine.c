/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:58:43 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/15 10:36:17 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void take_one(t_philo *p)
{
    pthread_mutex_lock(p->left);
    log_state(p, "has taken a fork");
}

static void take_two(t_philo *p)
{
    pthread_mutex_lock(p->left);
    log_state(p, "has taken a fork");
    pthread_mutex_lock(p->right);
    log_state(p, "has taken a fork");
}

static void do_eat(t_philo *p)
{
    pthread_mutex_lock(&p->rules->meal_lock);
    p->last_meal = timestamp_ms();
    pthread_mutex_unlock(&p->rules->meal_lock);
    log_state(p, "is eating");
    ft_usleep(p->rules->t_eat);
    pthread_mutex_unlock(p->left);
    pthread_mutex_unlock(p->right);
    p->meals_eaten++;
}

void *philo_routine(void *arg)
{
    t_philo *p = (t_philo *)arg;

    if (p->rules->n_philo == 1)
    {
        take_one(p);                 /* now the helper is used */
        ft_usleep(p->rules->t_die);
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
        ft_usleep(p->rules->t_sleep);
        log_state(p, "is thinking");
    }
    return (NULL);
}
