/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 06:28:44 by jgoldste          #+#    #+#             */
/*   Updated: 2022/06/02 06:54:37 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

#include <errno.h>
#include <string.h>

# define FORKS "forks"
# define PRINT "print"
# define STOP "stop"
# define MEALS_SEM "meals_sem"
# define DEATH_SEM "death_sem"

typedef struct s_philo
{
	int				id;
	int				meals;
	long long		death_time;
	long long		last_meal;
	sem_t			*death_sem;
}	t_philo;

typedef struct s_params
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	int				philo_exit;
	int				philos_had_eaten;
	long long		start;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*stop;
	sem_t			*meals_sem;
	pid_t			*pid;
	t_philo			*philo;
}	t_params;

t_params	*validation(t_params *params, char **argv);
int			valid_args(t_params *params);
int			malloc_pid(t_params *params);
int			init_philo(t_params *params);
int			init_sem(t_params *params);
int			ft_sem_close(t_params *params);

int			launch(t_philo *philo, t_params *params);
int			philo_live(t_philo *philo, t_params *params);

long long	get_timestamp(void);
int			ft_sleep(long long m_secs, t_params *params);
int			print_status(t_philo *philo, t_params *params, char *action);
void		free_null(void *ptr);
t_params	*free_return(t_params *params);
int			error_code(int code);
int			error_code_free_exit(int code, t_params *params);

#endif