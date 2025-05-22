/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:24:41 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/22 14:24:43 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <semaphore.h>

static sem_t	g_waiter;

void	waiter_init(int slots)		{ sem_init(&g_waiter, 0, slots); }
void	waiter_destroy(void)		{ sem_destroy(&g_waiter); }
void	waiter_take(void)			{ sem_wait(&g_waiter); }
void	waiter_give(void)			{ sem_post(&g_waiter); }
