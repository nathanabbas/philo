/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:39:00 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/22 15:39:02 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	timestamp_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(t_rules *r, long ms)
{
	long	target;

	target = timestamp_ms() + ms;
	while (timestamp_ms() < target && !is_dead(r) && !all_fed(r))
		usleep(500);
}
