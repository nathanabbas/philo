
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:02:00 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/21 21:00:00 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* -------------------------------------------------------------------------- */
/*  Child-side death monitor thread                                            */
/* -------------------------------------------------------------------------- */
void *monitor(void *arg)
{
    t_philo *p = (t_philo *)arg;

    while (1)
    {
        sem_wait(p->lock);
        if (get_time_ms() - p->last_meal > p->rules->t_die)
        {
            sem_post(p->lock);
            log_state(p, "died", true);
            /* signal all via stop_flag */
            sem_wait(p->rules->print);
            p->rules->stop_flag = 1;
            sem_post(p->rules->print);
            /* wake parent if blocked */
            sem_post(p->rules->stop);
            exit(1);
        }
        sem_post(p->lock);
        if (p->rules->t_die > 60000)
            usleep(10000);
        else
            usleep(1000);
    }
    return (NULL);
}

/* -------------------------------------------------------------------------- */
/*  Parent: wait for children, then cleanup & exit                             */
/* -------------------------------------------------------------------------- */
void parent_watch(t_rules *r)
{
	int   finished = 0;
	int   st;
	pid_t pid;
	int   i;

	while (finished < r->n_philo)
	{
		pid = waitpid(-1, &st, 0);
		if (pid <= 0)
			continue;
		if (!WIFEXITED(st) || WEXITSTATUS(st) != 0)
		{
			i = 0;
			while (i < r->n_philo)
				kill(r->pids[i++], SIGTERM);
			break;
		}
		finished++;
	}
	free_all(r);
	exit(0); // Critical to ensure parent terminates immediately
}
