/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:42:45 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/22 15:48:54 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	start_philos(t_rules *r)
{
	int	i;

	i = -1;
	while (++i < r->n_philo)
	{
		r->pids[i] = fork();
		if (r->pids[i] == 0)
		{
			if (pthread_create(&r->philos[i].mon, 0,
					monitor, &r->philos[i]) != 0)
				exit(1);
			routine(&r->philos[i]);
			exit(0);
		}
	}
}

int	main(int ac, char **av)
{
	t_rules	r;

	if (!parse_args(ac, av, &r))
		return (printf("invalid argument\n"), 1);
	if (!init_sim(&r))
		return (printf("init error\n"), 1);
	start_philos(&r);
	parent_watch(&r);
	free_all(&r);
	return (0);
}
