/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:42:07 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/22 16:59:57 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	log_state(t_philo *p, char *msg, int death)
{
	long	ts;

	sem_wait(p->rules->stop);
	if (!p->rules->stop_flag || death)
	{
		if (death)
			p->rules->stop_flag = 1;
		sem_post(p->rules->stop);
		ts = get_time_ms() - p->rules->start;
		sem_wait(p->rules->print);
		printf("%ld %d %s\n", ts, p->id, msg);
		sem_post(p->rules->print);
		return ;
	}
	sem_post(p->rules->stop);
}
