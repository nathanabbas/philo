/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22                                    */
/*   Updated: 2025/05/24                                    */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* ---------------------------------------------------------- */
/*  ft_atol : strict, 32-bit positive, returns -1 on invalid   */
/* ---------------------------------------------------------- */
static long	ft_atol(char *s)
{
	long	n;

	n = 0;
	if (!*s)
		return (-1);
	while (*s >= '0' && *s <= '9')
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

/* ---------------------------------------------------------- */
/*  fill_rules : convert argv → rules, basic sanity checks    */
/* ---------------------------------------------------------- */
static int	fill_rules(char **av, t_rules *r)
{
	r->n_philo  = (int)ft_atol(av[1]);
	r->t_die    = ft_atol(av[2]);
	r->t_eat    = ft_atol(av[3]);
	r->t_sleep  = ft_atol(av[4]);
	if (av[5])
		r->meals_target = (int)ft_atol(av[5]);
	else
		r->meals_target = -1;

	if (r->n_philo < 1 || r->t_die <= 0 || r->t_eat <= 0 || r->t_sleep <= 0)
		return (1);
	return (0);
}

/* ---------------------------------------------------------- */
/*  parse_args : public entry, also init control flags        */
/* ---------------------------------------------------------- */
int	parse_args(int ac, char **av, t_rules *r)
{
	if (ac != 5 && ac != 6)
		return (1);
	if (fill_rules(av, r))
		return (1);
	r->someone_died = 0;
	r->fed_count    = 0;      /* initialise new fed counter */
	return (0);
}
