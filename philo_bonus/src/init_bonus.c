/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:02:29 by nabbas            */
/*   Updated: 2025/06/21 17:10:00 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* -------------------------------------------------------------------------- */
/*  Create / reopen named semaphores (n − 1 seat rule)                        */
/* -------------------------------------------------------------------------- */
static int open_sems(t_rules *r)
{
    int waiter_cap;

    sem_unlink("/slots");
    sem_unlink("/forks");
    sem_unlink("/print");
    sem_unlink("/stop");
    waiter_cap = r->n_philo - 1;
    if (waiter_cap == 0)
        waiter_cap = 1;
    r->slots = sem_open("/slots", O_CREAT, 0644, waiter_cap);
    r->forks = sem_open("/forks", O_CREAT, 0644, r->n_philo);
    r->print = sem_open("/print", O_CREAT, 0644, 1);
    r->stop  = sem_open("/stop",  O_CREAT, 0644, 0);
    if (r->slots == SEM_FAILED || r->forks == SEM_FAILED
     || r->print == SEM_FAILED || r->stop == SEM_FAILED)
        return (0);
    return (1);
}

/* -------------------------------------------------------------------------- */
/*  Allocate & init arrays                                                    */
/* -------------------------------------------------------------------------- */
static bool setup_arrays(t_rules *r)
{
    int  i;
    char name[32];

    i = -1;
    r->stop_flag = 0;
    if (!open_sems(r))
        return (false);
    r->philos = malloc(sizeof(t_philo) * r->n_philo);
    r->pids   = malloc(sizeof(pid_t)  * r->n_philo);
    if (!r->philos || !r->pids)
        return (false);
    while (++i < r->n_philo)
    {
        r->philos[i].id        = i + 1;
        r->philos[i].meals     = 0;
        r->philos[i].last_meal = 0;
        r->philos[i].rules     = r;
        build_sem_name(name, i);
        sem_unlink(name);
        r->philos[i].lock = sem_open(name, O_CREAT, 0644, 1);
        if (r->philos[i].lock == SEM_FAILED)
            return (false);
    }
    return (true);
}

/* -------------------------------------------------------------------------- */
/*  Spawn one philosopher process                                             */
/* -------------------------------------------------------------------------- */
static int start_child(t_rules *r, int i)
{
    pid_t pid;

    pid = fork();
    if (pid < 0)
        return (1);
    if (pid == 0)
    {
        if (philo_life(&r->philos[i]))
            exit(2);
        exit(0);
    }
    r->pids[i] = pid;
    return (0);
}

/* -------------------------------------------------------------------------- */
/*  Public simulator entry                                                   */
/* -------------------------------------------------------------------------- */
bool init_sim(t_rules *r)
{
    int i;

    i = -1;
    if (!setup_arrays(r))
        return (false);
    r->start = get_time_ms();
    while (++i < r->n_philo)
        if (start_child(r, i))
            return (false);
    return (true);
}
