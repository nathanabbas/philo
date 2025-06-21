/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:09:08 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/21 19:29:10 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void take_forks(t_philo *p)
{
    sem_wait(p->rules->slots);
    sem_wait(p->rules->forks);
    log_state(p, "has taken a fork", false);
    sem_wait(p->rules->forks);
    log_state(p, "has taken a fork", false);
}

static void drop_forks(t_philo *p)
{
    sem_post(p->rules->forks);
    sem_post(p->rules->forks);
    sem_post(p->rules->slots);
}

void think(t_philo *p)
{
    long slack;
    long win;

    slack = p->rules->t_die
          - (p->rules->t_eat + p->rules->t_sleep);
    if (slack <= 0)
        win = 0;
    else if (slack > 600)
        win = 200;
    else
        win = slack / 2;
    log_state(p, "is thinking", false);
    smart_sleep(win, p->rules);
}

void eat(t_philo *p)
{
    take_forks(p);
    sem_wait(p->lock);
    p->last_meal = get_time_ms();
    sem_post(p->lock);
    log_state(p, "is eating", false);
    ft_usleep(p->rules->t_eat);
    sem_wait(p->lock);
    p->meals++;
    p->last_meal = get_time_ms();
    sem_post(p->lock);
    drop_forks(p);
}

void sleep_philo(t_philo *p)
{
    log_state(p, "is sleeping", false);
    smart_sleep(p->rules->t_sleep, p->rules);
}
