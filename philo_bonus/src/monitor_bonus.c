/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:56:18 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/22 16:24:39 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:41:47 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/22 15:55:02 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (1)
	{
		sem_wait(p->lock);
		if (get_time_ms() - p->last_meal >= p->rules->t_die)
		{
			sem_post(p->lock);
			log_state(p, "died", 1);
			exit(1);
		}
		sem_post(p->lock);
		usleep(1000);
	}
	return (0);
}

void	parent_watch(t_rules *r)
{
	int	i;
	int	status;

	i = -1;
	while (++i < r->n_philo)
	{
		if (waitpid(-1, &status, 0) == -1)
			break ;
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			i = -1;
			while (++i < r->n_philo)
				kill(r->pids[i], SIGKILL);
			break ;
		}
	}
}
