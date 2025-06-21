/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:33:32 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/21 19:30:24 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void log_state(t_philo *p, const char *msg, bool death)
{
    long ts;

    sem_wait(p->rules->print);
    ts = get_time_ms() - p->rules->start;
    printf("%ld %d %s\n", ts, p->id, msg);
    if (!death)
        sem_post(p->rules->print);
}
