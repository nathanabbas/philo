/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:27:09 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/26 12:27:11 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	valid_int(long v)
{
	return (v > 0 && v <= INT_MAX);
}

bool	parse_args(int ac, char **av, t_rules *r)
{
	bool	ok;
	long	tmp;

	if (ac != 5 && ac != 6)
		return (false);
	ok = true;
	tmp = ft_atoi_pos(av[1], &ok);
	r->n_philo = (int)tmp;
	r->t_die = (int)ft_atoi_pos(av[2], &ok);
	r->t_eat = (int)ft_atoi_pos(av[3], &ok);
	r->t_sleep = (int)ft_atoi_pos(av[4], &ok);
	r->must_eat = -1;
	if (ac == 6)
		r->must_eat = (int)ft_atoi_pos(av[5], &ok);
	if (!ok || !valid_int(r->n_philo) || !valid_int(r->t_die)
		|| !valid_int(r->t_eat) || !valid_int(r->t_sleep)
		|| (ac == 6 && !valid_int(r->must_eat)))
		return (false);
	return (true);
}
