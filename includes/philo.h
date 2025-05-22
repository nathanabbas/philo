/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:31:12 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/22 15:31:47 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_rules	t_rules;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	long			last_meal;
	int				meals_eaten;
	t_rules			*rules;
}	t_philo;

struct s_rules
{
	int				n_philo;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	int				meals_target;
	long			start_ts;
	int				someone_died;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	*forks;
	sem_t			waiter;
	t_philo			*philos;
	pthread_t		monitor;
};

long	timestamp_ms(void);
void	ft_usleep(t_rules *rules, long ms);

int		parse_args(int ac, char **av, t_rules *rules);

void	log_state(t_philo *philo, char *msg);
int		is_dead(t_rules *rules);
int		all_fed(t_rules *rules);

int		init_simulation(t_rules *rules);
void	clean_exit(t_rules *rules, int code);

void	*philo_routine(void *arg);
void	*monitor_routine(void *arg);

void	waiter_init(t_rules *rules, int slots);
void	waiter_destroy(t_rules *rules);
void	waiter_take(t_rules *rules);
void	waiter_give(t_rules *rules);

#endif
