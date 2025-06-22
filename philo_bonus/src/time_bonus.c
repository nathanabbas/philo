/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:44:12 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/22 17:00:42 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long ms)
{
	long	start;

	start = get_time_ms();
	while (get_time_ms() - start < ms)
		usleep(100);
}

void	smart_sleep(long dur, t_rules *r)
{
	long	start;

	start = get_time_ms();
	while (get_time_ms() - start < dur)
	{
		usleep(100);
		sem_wait(r->stop);
		if (r->stop_flag)
		{
			sem_post(r->stop);
			break ;
		}
		sem_post(r->stop);
	}
}
