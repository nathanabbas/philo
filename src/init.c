/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:38:06 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/24 13:54:17 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int  create_mutexes(t_rules *r)
{
    int i;

    if (pthread_mutex_init(&r->print_lock, NULL))
        return (1);
    if (pthread_mutex_init(&r->meal_lock, NULL))
        return (1);
    r->forks = malloc(sizeof(pthread_mutex_t) * r->n_philo);
    if (!r->forks)
        return (1);
    i = 0;
    while (i < r->n_philo)
        if (pthread_mutex_init(&r->forks[i++], NULL))
            return (1);
    return (0);
}

static void assign_forks(t_rules *r)
{
    int i = 0;

    while (i < r->n_philo)
    {
        r->philos[i].left  = &r->forks[i];
        r->philos[i].right = &r->forks[(i + 1) % r->n_philo];
        i++;
    }
}

int init_simulation(t_rules *r)
{
    int i;

    if (create_mutexes(r))
        return (1);
    r->philos = malloc(sizeof(t_philo) * r->n_philo);
    if (!r->philos)
        return (1);
    i = 0;
    while (i < r->n_philo)
    {
        r->philos[i].id          = i + 1;
        r->philos[i].meals_eaten = 0;
        r->philos[i].last_meal   = 0;
        r->philos[i].rules       = r;
        i++;
    }
    assign_forks(r);
    return (0);
}
