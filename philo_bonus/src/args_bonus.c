/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 13:47:26 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/21 19:29:02 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* helper: check that v ∈ [1‥INT_MAX] */
static bool valid(long v)
{
    return (v > 0 && v <= INT_MAX);
}

bool parse_args(int ac, char **av, t_rules *r)
{
    bool ok;
    long t;

    if (ac != 5 && ac != 6)
        return (false);
    ok = true;
    t = ft_atoi_pos(av[1], &ok);
    r->n_philo = (int)t;
    r->t_die   = ft_atoi_pos(av[2], &ok);
    r->t_eat   = ft_atoi_pos(av[3], &ok);
    r->t_sleep = ft_atoi_pos(av[4], &ok);
    r->must_eat = -1;
    if (ac == 6)
        r->must_eat = ft_atoi_pos(av[5], &ok);
    if (!ok
     || !valid(r->n_philo)
     || !valid(r->t_die)
     || !valid(r->t_eat)
     || !valid(r->t_sleep)
     || (ac == 6 && (!valid(r->must_eat) || r->must_eat == 0)))
        return (false);
    return (true);
}

