/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:09:55 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/24 13:53:41 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor_routine(void *arg)
{
    t_rules *r = arg;
    int      i;
    long     now;

    while (!all_fed(r) && !is_dead(r))
    {
        pthread_mutex_lock(&r->meal_lock);
        i = 0;
        while (i < r->n_philo)
        {
            now = timestamp_ms();
            if (now - r->philos[i].last_meal >= r->t_die)
            {
                r->someone_died = 1;
                pthread_mutex_unlock(&r->meal_lock);
                pthread_mutex_lock(&r->print_lock);
                printf("%ld %d died\n",
                       now - r->start_ts,
                       r->philos[i].id);
                pthread_mutex_unlock(&r->print_lock);
                return (NULL);
            }
            i++;
        }
        pthread_mutex_unlock(&r->meal_lock);
        ft_usleep(r, 1);
    }
    return (NULL);
}
