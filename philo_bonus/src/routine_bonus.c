/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:25:25 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/21 19:29:41 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* -------------------------------------------------------------------------- */
/*  helpers                                                                   */
/* -------------------------------------------------------------------------- */
static void close_child_sems(t_rules *r)
{
    sem_close(r->forks);
    sem_close(r->print);
    sem_close(r->slots);
    sem_close(r->stop);
}

static int done_eating(t_philo *p)
{
    int ret;

    if (p->rules->must_eat == -1)
        return (0);
    sem_wait(p->lock);
    ret = (p->meals >= p->rules->must_eat);
    sem_post(p->lock);
    return (ret);
}

static int got_stop(t_philo *p)
{
    int ret;

    sem_wait(p->rules->print);
    ret = p->rules->stop_flag;
    sem_post(p->rules->print);
    return (ret);
}

/* -------------------------------------------------------------------------- */
/*  compute initial delay                                                     */
/* -------------------------------------------------------------------------- */
static long init_delay(t_philo *p)
{
    if ((p->rules->n_philo & 1) == 0
        && p->rules->t_die < p->rules->t_eat + p->rules->t_sleep
        && (p->id & 1))
        return ((p->rules->t_eat + p->rules->t_sleep) * 1000);
    if (p->rules->n_philo > 3 && (p->id & 1))
        return (1000);
    return (0);
}

/* -------------------------------------------------------------------------- */
/*  main routine                                                              */
/* -------------------------------------------------------------------------- */
int philo_life(t_philo *p)
{
    long d;

    p->last_meal = get_time_ms();
    if (pthread_create(&p->mon, NULL, monitor, p))
        return (1);
    pthread_detach(p->mon);
    d = init_delay(p);
    if (d)
        usleep(d);
    while (!got_stop(p))
    {
        eat(p);
        if (done_eating(p))
        {
            close_child_sems(p->rules);
            exit(0);
        }
        sleep_philo(p);
        think(p);
    }
    close_child_sems(p->rules);
    exit(1);
}
