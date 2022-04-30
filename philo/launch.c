/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 01:53:06 by jgoldste          #+#    #+#             */
/*   Updated: 2022/05/01 02:55:42 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*test(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->mutex);
	printf("MUTEX_LOCK_UNLOCK ID[%d]\n", philo->id);
	pthread_mutex_unlock(&philo->mutex);
	return((void *)philo);
}

static t_philo	philo_init(int id, t_params *params)
{
	t_philo	philo;

	philo.id = id;
	philo.left_fork = 0;
	philo.right_fork = 0;
	philo.params = params;
	return (philo);
}

int	launch(t_params *params)
{
	int			id;
	
	// pthread_mutex_init(&params->mutex, NULL);
	id = 0;
	while (id < params->num_of_philo)
	{
		params->philo[id] = philo_init(id, params);
		pthread_mutex_init(&params->philo[id].mutex, NULL);
		if (pthread_create(&params->thread[id], NULL, &test, &params->philo[id]))
			return (5);
		printf("THREAD [%d] IS CREATED\n", id);
		id++;
	}
	id = 0;
	while (id < params->num_of_philo)
	{
		if (pthread_join(params->thread[id], NULL))
			return (6);
		printf("THREAD [%d] IS FINISHED\n", id);
		pthread_mutex_destroy(&params->philo[id].mutex);
		id++;
	}
	// pthread_mutex_destroy(&params->mutex);
	return (0);
}

// printf("num_of_philo = %d\ntime_to_die = %d\ntime_to_eat = %d\ntime_to_sleep = %d\ntimes_must_eat = %d\n",
// 		params->num_of_philo, params->time_to_die, params->time_to_eat, params->time_to_sleep, params->times_must_eat);
