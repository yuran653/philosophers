/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:57:21 by jgoldste          #+#    #+#             */
/*   Updated: 2022/05/01 02:54:53 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	struct s_params	*params;
	pthread_mutex_t	mutex;
}	t_philo;

typedef struct s_params
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	t_philo			*philo;
	pthread_t		*thread;
	pthread_mutex_t	mutex;
}	t_params;

t_params	*validation(t_params *params, char **argv);
int			launch(t_params *params);

#endif