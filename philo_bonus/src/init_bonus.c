/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:40:36 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/22 15:52:25 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void set_philo(t_rules *r, int i)
{
	t_philo *p = &r->philos[i];
	p->id = i + 1;
	p->meals = 0;
	p->rules = r;
	p->last_meal = r->start;
	char name[20];
	build_sem_name(name, i);
	sem_unlink(name);
	p->lock = sem_open(name, O_CREAT, 0644, 1);
}

bool	init_sim(t_rules *r)
{
	int	i;

	i = -1;
	r->start = get_time_ms();
	r->stop_flag = 0;
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/stop");
	sem_unlink("/slots");
	r->forks = sem_open("/forks", O_CREAT, 0644, r->n_philo);
	r->print = sem_open("/print", O_CREAT, 0644, 1);
	r->stop = sem_open("/stop", O_CREAT, 0644, 1);
	r->slots = sem_open("/slots", O_CREAT, 0644, r->n_philo);
	r->philos = malloc(sizeof(t_philo) * r->n_philo);
	r->pids = malloc(sizeof(pid_t) * r->n_philo);
	if (!r->philos || !r->forks || !r->print || !r->stop || !r->slots)
		return (0);
	while (++i < r->n_philo)
		set_philo(r, i);
	return (1);
}
