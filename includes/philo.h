/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:06:28 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/24 14:06:29 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_rules t_rules;
typedef struct s_philo t_philo;

struct s_philo
{
	int             id;             /* 1-based */
	pthread_t       thread;
	pthread_mutex_t *left;
	pthread_mutex_t *right;
	long            last_meal;
	int             meals_eaten;
	t_rules         *rules;
};

struct s_rules
{
	int             n_philo;
	long            t_die;
	long            t_eat;
	long            t_sleep;
	int             meals_target;
	long            start_ts;
	int             someone_died;
	int             fed_count;      /* NEW: #philos who hit meals_target */
	pthread_mutex_t print_lock;
	pthread_mutex_t meal_lock;
	pthread_mutex_t *forks;
	t_philo         *philos;
	pthread_t       monitor;
};

long	timestamp_ms(void);
void	ft_usleep(t_rules *r, long ms);

int		parse_args(int ac, char **av, t_rules *r);
void	log_state(t_philo *p, const char *msg);
int		is_dead(t_rules *r);
int		all_fed(t_rules *r);

int		init_simulation(t_rules *r);
void	clean_exit(t_rules *r, int code);

void	*philo_routine(void *arg);
void	*monitor_routine(void *arg);
#endif
