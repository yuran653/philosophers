/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:57:21 by jgoldste          #+#    #+#             */
/*   Updated: 2022/05/28 20:20:26 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef union s_forks
{
	pthread_mutex_t	*fork;
}	t_forks;

typedef union s_print
{
	pthread_mutex_t	mut;
}	t_print;

typedef union s_death
{
	pthread_mutex_t	mut;
}	t_death;

typedef union s_meals
{
	pthread_mutex_t	mut;
}	t_meals;

typedef struct s_philo
{
	int				id;
	int				meals;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	int				right_fork;
	int				left_fork;
	long long		death_time;
	long long		last_meal;
	long long		start;
	t_forks			*forks;
	t_print			*print;
	t_meals			*meals_mut;
	struct s_params	*params;
	pthread_mutex_t	mut_death;
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
	t_philo			*philo;
	t_forks			*forks;
	t_print			*print;
	t_death			*death;
	t_meals			*meals_mut;
	pthread_t		*thread;
}	t_params;

t_params	*validation(t_params *params, char **argv);
int			valid_args(t_params *params);
int			malloc_arrays(t_params *params, int size);
void		philos_init(t_params *params);
int			mutex_init(t_params *params);
int			mutex_destroy(t_params *params);
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