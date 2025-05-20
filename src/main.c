/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:59:07 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/15 09:59:08 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	start_threads(t_rules *r)
{
	int	i;

	r->start_ts = timestamp_ms();
	i = 0;
	while (i < r->n_philo)
	{
		r->philos[i].last_meal = r->start_ts;
		if (pthread_create(&r->philos[i].thread, NULL,
				philo_routine, &r->philos[i]))
			return (1);
		i++;
	}
	if (pthread_create(&r->monitor, NULL, monitor_routine, r))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_rules	r;

	if (parse_args(ac, av, &r))
		return (printf("Error: bad arguments\n"), 1);
	if (init_simulation(&r))
		return (printf("Error: init failed\n"), 1);
	if (start_threads(&r))
		return (printf("Error: thread failure\n"), 1);
	clean_exit(&r, 0);
	return (0);
}
