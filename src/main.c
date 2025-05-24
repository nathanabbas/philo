/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:40:01 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/24 13:53:06 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int start_threads(t_rules *r)
{
    int i;

    r->start_ts = timestamp_ms();
    i = 0;
    while (i < r->n_philo)
    {
        r->philos[i].last_meal = r->start_ts;
        if (pthread_create(&r->philos[i].thread,
                           NULL,
                           philo_routine,
                           &r->philos[i]))
            return (1);
        i++;
    }
    if (pthread_create(&r->monitor, NULL, monitor_routine, r))
        return (1);
    return (0);
}

int main(int ac, char **av)
{
    t_rules r;

    if (parse_args(ac, av, &r))
    {
        printf("Error: bad arguments\n");
        return (1);
    }
    if (init_simulation(&r))
    {
        printf("Error: init failed\n");
        return (1);
    }
    if (start_threads(&r))
    {
        printf("Error: thread failure\n");
        return (1);
    }
    clean_exit(&r, 0);
    return (0);
}
