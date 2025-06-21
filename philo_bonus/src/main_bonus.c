/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:02:29 by nabbas            */
/*   Updated: 2025/06/21 17:10:00 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo_bonus.h"

static int solo_case(t_rules *r)
{
	r->start = get_time_ms();
	printf("0 1 has taken a fork\n");
	ft_usleep(r->t_die);
	printf("%d 1 died\n", r->t_die);
	return (0);
}

int main(int ac, char **av)
{
	t_rules r;

	if (!parse_args(ac, av, &r))
		return (printf("invalid argument\n"), 1);
	if (r.n_philo == 1)
		return (solo_case(&r));
	if (!init_sim(&r))
		return (printf("init error\n"), 1);
	parent_watch(&r);
	return (0); // No free_all here, it's handled by parent_watch
}

