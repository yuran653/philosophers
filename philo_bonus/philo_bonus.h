/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 06:28:44 by jgoldste          #+#    #+#             */
/*   Updated: 2022/06/07 14:16:00 by jgoldste         ###   ########.fr       */
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

# define FORKS "forks"
# define PRINT "print"
# define DEATH "death"
# define PHILOS_HAD_EATEN "philos_had_eaten"

typedef struct s_philo
{
	int			id;
	int			meals;
	long long	death_time;
	long long	last_meal;
}	t_philo;

typedef struct s_params
{
	int			num_of_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			times_must_eat;
	long long	start;
	sem_t		*forks;
	sem_t		*print;
	sem_t		*philos_had_eaten;
	pid_t		*pid;
	t_philo		*philo;
}	t_params;

t_params	*validation(t_params *params, char **argv);
int			valid_args(t_params *params);
int			calloc_pid(t_params *params);
int			init_philo(t_params *params);
int			init_sem(t_params *params);
sem_t		*ft_sem_open(char *name, int oflag, mode_t mode, int value);
int			launch(t_philo *philo, t_params *params);
void		philo_live(t_philo *philo, t_params *params);
long long	get_timestamp(void);
void		ft_sleep(long long m_secs);
void		print_status(t_philo *philo, t_params *params, char *action);
void		wait_exit_status(t_params *params, int id);
int			kill_all_processes(t_params *params, int id, int value);
void		sem_close_unlink(sem_t *sem, char *name);
void		free_null(void *ptr);
t_params	*free_return(t_params *params);
int			error_code(int code);
int			error_code_free_exit(int code, t_params *params);

#endif