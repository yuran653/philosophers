/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:57:21 by jgoldste          #+#    #+#             */
/*   Updated: 2022/05/03 06:36:53 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

// typedef enum s_even_odd
// {
// 	EVEN = 2,
// 	ODD = 1
// }	t_even_odd;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals;
	// int				left_fork;
	// int				right_fork;
	pthread_mutex_t	fork;
	pthread_mutex_t	*fork_next;
	struct s_params	*params;
}	t_philo;

typedef struct s_params
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	int				philos_have_eaten;
	int				turn;
	int				even_half;
	int				odd_half;
	// t_even_odd		even_odd;
	t_philo			*philo;
	pthread_mutex_t	print;
}	t_params;

t_params	*validation(t_params *params, char **argv);
int			philos_init(t_params *params);
// int			mutex_init(t_params *params);
int			mutex_destroy(t_params *params);
long long	get_timestamp(void);
int			launch(t_params *params);

#endif