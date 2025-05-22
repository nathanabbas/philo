/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:00:00 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/22 15:10:40 by nabbas           ###   ########.fr       */
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

/* ─────── structs ────────────────────────────────────────────────────────── */

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

struct	s_rules
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
	sem_t			waiter;        /* <── semaphore now lives here */
	t_philo			*philos;
	pthread_t		monitor;
};

/* ─────── utils_time.c ───────────────────────────────────────────────────── */

long	timestamp_ms(void);
void	ft_usleep(t_rules *r, long ms);

/* ─────── utils_parse.c ──────────────────────────────────────────────────── */

int		parse_args(int ac, char **av, t_rules *r);

/* ─────── log.c ──────────────────────────────────────────────────────────── */

void	log_state(t_philo *p, char *msg);
int		is_dead(t_rules *r);
int		all_fed(t_rules *r);

/* ─────── init.c / cleanup.c ─────────────────────────────────────────────── */

int		init_simulation(t_rules *r);
void	clean_exit(t_rules *r, int code);

/* ─────── routine / monitor ──────────────────────────────────────────────── */

void	*philo_routine(void *arg);
void	*monitor_routine(void *arg);

/* ─────── waiter.c (bonus starvation guard) ──────────────────────────────── */



static inline void	waiter_init(t_rules *r, int slots)
						{ sem_init(&r->waiter, 0, slots); }
static inline void	waiter_destroy(t_rules *r)
						{ sem_destroy(&r->waiter); }
static inline void	waiter_take(t_rules *r)   { sem_wait(&r->waiter); }
static inline void	waiter_give(t_rules *r)   { sem_post(&r->waiter); }

#endif
