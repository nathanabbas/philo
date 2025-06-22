/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:50:15 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/22 16:55:31 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <pthread.h>
# include <signal.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_rules	t_rules;

typedef struct s_philo
{
	int			id;
	long		last_meal;
	int			meals;
	pid_t		pid;
	pthread_t	mon;
	t_rules		*rules;
	sem_t		*lock;
}	t_philo;

struct s_rules
{
	int		n_philo;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		must_eat;
	long	start;
	int		stop_flag;
	sem_t	*forks;
	sem_t	*print;
	sem_t	*stop;
	sem_t	*slots;
	t_philo	*philos;
	pid_t	*pids;
};

/* args_bonus.c */
int		ft_atoi_pos(const char *s, int *ok);
int		parse_args(int ac, char **av, t_rules *r);

/* time_bonus.c */
long	get_time_ms(void);
void	ft_usleep(long ms);
void	smart_sleep(long ms, t_rules *r);

/* utils_bonus.c */
void	build_sem_name(char *dst, int idx);

/* actions_bonus.c */
void	eat(t_philo *p);
void	sleep_philo(t_philo *p);
void	think(t_philo *p);

/* monitor_bonus.c */
void	*monitor(void *arg);
void	parent_watch(t_rules *r);

/* print_bonus.c */
void	log_state(t_philo *p, char *msg, int death);

/* cleanup_bonus.c */
void	free_all(t_rules *r);

/* routine_bonus.c */
void	*routine(void *arg);

/* init_bonus.c */
bool	init_sim(t_rules *r);

#endif
