/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:28:09 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/19 19:33:27 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_state(t_philo *p, const char *msg, bool death)
{
	long	ts;

	pthread_mutex_lock(&p->rules->sim_lock);
	if (!p->rules->stop || death)
	{
		ts = get_time_ms() - p->rules->start;
		pthread_mutex_lock(&p->rules->print);
		printf("%ld %d %s\n", ts, p->id, msg);
		pthread_mutex_unlock(&p->rules->print);
	}
	pthread_mutex_unlock(&p->rules->sim_lock);
}
