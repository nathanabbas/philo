/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:48:13 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/21 19:28:25 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>

/* ----------------------------------------------------------------- */
/*  Core structs                                                     */
/* ----------------------------------------------------------------- */
typedef struct s_rules t_rules;

typedef struct s_philo
{
    int       id;
    long      last_meal;
    int       meals;
    pthread_t mon;
    sem_t    *lock;      /* named semaphore per-philosopher */
    t_rules  *rules;
} t_philo;

struct s_rules
{
    int     n_philo;
    int     t_die;
    int     t_eat;
    int     t_sleep;
    int     must_eat;
    long    start;
    sem_t  *forks;
    sem_t  *slots;
    sem_t  *print;
    sem_t  *stop;
    int     stop_flag;   /* signaled on death */
    t_philo *philos;
    pid_t  *pids;
};

/* ----------------------------------------------------------------- */
/*  Prototypes                                                       */
/* ----------------------------------------------------------------- */
/* parsing / init */
bool    parse_args(int ac, char **av, t_rules *r);
bool    init_sim(t_rules *r);

/* actions & routine */
int     philo_life(t_philo *p);
void    eat(t_philo *p);
void    think(t_philo *p);
void    sleep_philo(t_philo *p);

/* monitor & parent */
void   *monitor(void *arg);
void    parent_watch(t_rules *r);

/* timing & helpers */
long    get_time_ms(void);
void    ft_usleep(long ms);
int     ft_atoi_pos(const char *s, bool *ok);
void    smart_sleep(long dur, t_rules *r);
void    build_sem_name(char *dst, int idx);

/* logging + cleanup */
void    log_state(t_philo *p, const char *msg, bool death);
void    free_all(t_rules *r);

#endif /* PHILO_BONUS_H */
