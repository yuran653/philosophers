/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 06:28:44 by jgoldste          #+#    #+#             */
/*   Updated: 2022/06/01 06:28:47 by jgoldste         ###   ########.fr       */
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

typedef struct s_philo
{
	int				id;
	int				meals;
	long long		death_time;
	long long		last_meal;
	sem_t			death_sem;
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
	sem_t			forks;
	sem_t			print;
	sem_t			exit;
	sem_t			meals_sem;
	t_philo			*philo;
}	t_params;

t_params	*validation(t_params *params, char **argv);
int			valid_args(t_params *params);
int			init_philo(t_params *params);

int			launch(t_params *params);
void		*philo_live(void *ptr);
long long	get_timestamp(void);
int			ft_sleep(long long m_secs, t_params *params);
int			print_status(t_philo *philo, t_params *params, char *action);
int			mutex_unlock_return_1(t_philo *philo);
int			mutex_unlock_return_2(t_philo *philo);
void		free_null(void *ptr);
t_params	*free_return(t_params *params);
int			error_code(int code);
int			error_code_free_exit(int code, t_params *params);

#endif