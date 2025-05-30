/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:26:51 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/26 13:02:33 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_rules	t_rules;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	int				meals;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	lock;
	t_rules			*rules;
}	t_philo;

struct s_rules
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat;
	long			start;
	bool			stop;
	pthread_mutex_t	print;
	pthread_mutex_t	sim_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
};

/* args.c */
bool	parse_args(int ac, char **av, t_rules *r);
/* init.c */
bool	init_sim(t_rules *r);
/* routine.c */
void	*routine(void *arg);
/* monitor.c */
void	monitor(t_rules *r);
/* time.c */
long	get_time_ms(void);
void	ft_usleep(long ms);
/* print.c */
void	log_state(t_philo *p, const char *msg, bool death);
/* utils.c */
int		ft_atoi_pos(const char *s, bool *ok);
/* cleanup.c */
void	free_all(t_rules *r);


#endif

