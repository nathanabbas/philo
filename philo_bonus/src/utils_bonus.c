/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:44:27 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/22 15:57:24 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi_pos(const char *s, int *ok)
{
	long	res;

	res = 0;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '+')
		s++;
	if (*s < '0' || *s > '9')
		return (*ok = 0, 0);
	while (*s >= '0' && *s <= '9')
	{
		res = res * 10 + (*s - '0');
		if (res > INT_MAX)
			return (*ok = 0, 0);
		s++;
	}
	if (*s)
		return (*ok = 0, 0);
	return ((int)res);
}

void	build_sem_name(char *dst, int idx)
{
	int	i;

	i = 0;
	dst[i++] = '/';
	dst[i++] = 'p';
	dst[i++] = 'h';
	dst[i++] = 'i';
	dst[i++] = 'l';
	dst[i++] = 'o';
	dst[i++] = '_';
	dst[i++] = 'l';
	dst[i++] = 'o';
	dst[i++] = 'c';
	dst[i++] = 'k';
	dst[i++] = '_';
	if (idx >= 10)
		dst[i++] = '0' + (idx / 10);
	dst[i++] = '0' + (idx % 10);
	dst[i] = '\0';
}
