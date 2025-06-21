/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:49:18 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/21 19:30:15 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* positive-only atoi */
int ft_atoi_pos(const char *s, bool *ok)
{
    long n;

    n = 0;
    *ok = true;
    while (*s == ' ' || (*s >= 9 && *s <= 13))
        ++s;
    if (*s == '+')
        ++s;
    if (*s == '-' || !*s)
        return (*ok = false, -1);
    while (*s >= '0' && *s <= '9')
    {
        n = n * 10 + (*s++ - '0');
        if (n > INT_MAX)
            return (*ok = false, -1);
    }
    if (*s)
        return (*ok = false, -1);
    return ((int)n);
}

/* sleep <dur> ms, wake early on stop_flag */
void smart_sleep(long dur, t_rules *r)
{
    long start;

    start = get_time_ms();
    while (get_time_ms() - start < dur)
    {
        sem_wait(r->print);
        if (r->stop_flag)
        {
            sem_post(r->print);
            break ;
        }
        sem_post(r->print);
        usleep(100);
    }
}

/* build name "/lk_<idx>" without snprintf */
void build_sem_name(char *dst, int idx)
{
    int base;
    int i;

    dst[0] = '/'; dst[1] = 'l'; dst[2] = 'k'; dst[3] = '_';
    i = 0; base = 10;
    while (idx / base)
        base *= 10;
    while (base > 1)
    {
        base /= 10;
        dst[4 + i++] = '0' + (idx / base) % 10;
    }
    dst[4 + i] = '\0';
}
