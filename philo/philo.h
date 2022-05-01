/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:57:21 by jgoldste          #+#    #+#             */
/*   Updated: 2022/05/01 05:25:53 by jgoldste         ###   ########.fr       */
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
	int				left_fork;
	int				right_fork;
	struct s_params	*params;
	}	t_philo;

typedef struct s_params
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	t_philo			*philo;
	pthread_mutex_t	*forks;
}	t_params;

t_params	*validation(t_params *params, char **argv);
void		philos_init(t_params *params);
int			mutex_init(t_params *params);
int			mutex_destroy(t_params *params);
long int	get_timestamp(void);
int			launch(t_params *params);

#endif