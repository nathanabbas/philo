/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:58:13 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/15 09:58:15 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	ft_atol(char *s)
{
	long	n;

	n = 0;
	while (*s && (*s >= '0' && *s <= '9'))
	{
		n = (n * 10) + (*s - '0');
		if (n > 2147483647)
			return (-1);
		s++;
	}
	if (*s != '\0')
		return (-1);
	return (n);
}

static int	fill_rules(char **av, t_rules *r)
{
	r->n_philo = (int)ft_atol(av[1]);
	r->t_die = ft_atol(av[2]);
	r->t_eat = ft_atol(av[3]);
	r->t_sleep = ft_atol(av[4]);
	r->meals_target = -1;
	if (av[5])
		r->meals_target = (int)ft_atol(av[5]);
	if (r->n_philo < 1 || r->t_die < 0 || r->t_eat < 0 || r->t_sleep < 0)
		return (1);
	return (0);
}

int	parse_args(int ac, char **av, t_rules *r)
{
	if (ac != 5 && ac != 6)
		return (1);
	if (fill_rules(av, r))
		return (1);
	r->someone_died = 0;
	return (0);
}
