/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:44:00 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/22 15:44:01 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	valid_int(int n)
{
	return (n > 0 && n <= INT_MAX);
}

int	parse_args(int ac, char **av, t_rules *r)
{
	int	ok;

	if (ac != 5 && ac != 6)
		return (0);
	ok = 1;
	r->n_philo = ft_atoi_pos(av[1], &ok);
	r->t_die = ft_atoi_pos(av[2], &ok);
	r->t_eat = ft_atoi_pos(av[3], &ok);
	r->t_sleep = ft_atoi_pos(av[4], &ok);
	r->must_eat = -1;
	if (ac == 6)
		r->must_eat = ft_atoi_pos(av[5], &ok);
	if (!ok || !valid_int(r->n_philo) || !valid_int(r->t_die))
		return (0);
	if (!valid_int(r->t_eat) || !valid_int(r->t_sleep))
		return (0);
	if (ac == 6 && !valid_int(r->must_eat))
		return (0);
	return (1);
}
