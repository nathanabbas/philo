/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 19:32:56 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/21 19:33:01 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo_bonus.h"

/* -------------------------------------------------------------------------- */
/*  Free all resources and unlink named semaphores                            */
/* -------------------------------------------------------------------------- */
void	free_all(t_rules *r)
{
	char	name[32];
	int		i;

	i = -1;
	while (++i < r->n_philo)
	{
		build_sem_name(name, i);
		sem_close(r->philos[i].lock);
		sem_unlink(name);
	}
	free(r->philos);
	free(r->pids);
	sem_close(r->forks);
	sem_close(r->slots);
	sem_close(r->print);
	sem_close(r->stop);
	sem_unlink("/forks");
	sem_unlink("/slots");
	sem_unlink("/print");
	sem_unlink("/stop");
}
