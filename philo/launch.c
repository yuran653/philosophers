/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 01:53:06 by jgoldste          #+#    #+#             */
/*   Updated: 2022/05/01 05:23:31 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*test(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->params->forks[philo->id]);
	printf("MUTEX_LOCK_UNLOCK ID[%d]\n", philo->id);
	pthread_mutex_unlock(&philo->params->forks[philo->id]);
	return((void *)philo);
}

int	launch(t_params *params)
{
	int	id;
		
	id = 0;
	while (id < params->num_of_philo)
	{
		if (pthread_create(&params->philo[id].thread, NULL, &test, &params->philo[id]))
			return (7);
		printf("THREAD [%d] IS CREATED\n", id);
		id++;
	}
	id = 0;
	while (id < params->num_of_philo)
	{
		if (pthread_join(params->philo[id].thread, NULL))
			return (8);
		printf("THREAD [%d] IS FINISHED\n", id);
		id++;
	}
	return (0);
}

// printf("num_of_philo = %d\ntime_to_die = %d\ntime_to_eat = %d\ntime_to_sleep = %d\ntimes_must_eat = %d\n",
// 		params->num_of_philo, params->time_to_die, params->time_to_eat, params->time_to_sleep, params->times_must_eat);
