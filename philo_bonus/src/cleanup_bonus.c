/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:42:22 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/22 15:42:24 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void free_all(t_rules *r)
{
	int i = -1;
	char name[20];

	while (++i < r->n_philo)
	{
		build_sem_name(name, i);
		sem_close(r->philos[i].lock);
		sem_unlink(name);
	}
	sem_close(r->forks);
	sem_close(r->print);
	sem_close(r->stop);
	sem_close(r->slots);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/stop");
	sem_unlink("/slots");
	free(r->pids);
	free(r->philos);
}