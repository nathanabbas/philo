/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:28:59 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/19 19:32:30 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	one_philo_case(t_rules *r)
{
	long	ts;

	ts = 0;
	printf("%ld %d has taken a fork\n", ts, 1);
	ft_usleep(r->t_die);
	ts = r->t_die;
	printf("%ld %d died\n", ts, 1);
	return (0);
}

static void	wait_end(t_rules *r)
{
	int	i;

	monitor(r);
	i = -1;
	while (++i < r->n_philo)
		pthread_join(r->philos[i].thread, NULL);
}

int	main(int ac, char **av)
{
	t_rules	r;

	if (!parse_args(ac, av, &r))
		return (printf("invalid argument\n"), 1);
	if (r.n_philo == 1)
		return (one_philo_case(&r));
	if (!init_sim(&r))
		return (printf("Error: init failed\n"), 1);
	wait_end(&r);
	free_all(&r);
	return (0);
}
