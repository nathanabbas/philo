/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:40:47 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/22 15:40:48 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <semaphore.h>

void	waiter_init(t_rules *rules, int slots)
{
	sem_init(&rules->waiter, 0, slots);
}

void	waiter_destroy(t_rules *rules)
{
	sem_destroy(&rules->waiter);
}

void	waiter_take(t_rules *rules)
{
	sem_wait(&rules->waiter);
}

void	waiter_give(t_rules *rules)
{
	sem_post(&rules->waiter);
}
