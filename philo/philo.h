/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:57:21 by jgoldste          #+#    #+#             */
/*   Updated: 2022/05/04 05:45:37 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals;
	int				right_fork;
	int				left_fork;
	long long		start;
	struct s_params	*params;
}	t_philo;

typedef struct s_params
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	int				philo_is_dead;
	// long long		start;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}	t_params;

t_params	*validation(t_params *params, char **argv);
void		philos_init(t_params *params);
int			mutex_init(t_params *params);
int			mutex_destroy(t_params *params);
void		print_status(t_philo *philo, char *status);
long long	get_timestamp(void);
int			ft_sleep(long long m_secs, t_params *params);
int			launch(t_params *params);

#endif