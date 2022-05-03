/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 01:53:06 by jgoldste          #+#    #+#             */
/*   Updated: 2022/05/03 05:32:50 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*test(void *ptr)
{
	t_philo	*philo;
	
	philo = (t_philo *)ptr;
	while (1)
	{
		if ((philo->id + philo->params->turn) % 2 == 0)
		{
			pthread_mutex_lock(&philo->fork);
			pthread_mutex_lock(philo->fork_next);
			printf("\\-MUTEX_LOCK_ID-[%d]\n", philo->id);
			usleep(10000000);
			printf("\tPHILO[%2d] HAVE EATEN -%d-TIMES | TURN[%d] | MEALS[%d]\n",
				philo->id, ++philo->meals, philo->params->turn, philo->params->philos_have_eaten);
			philo->params->philos_have_eaten++;
			if (philo->params->turn % 2 == 1 && philo->params->philos_have_eaten == philo->params->odd_half)
			{
				philo->params->turn++;
				philo->params->philos_have_eaten = 0;
			}
			if (philo->params->turn % 2 == 0 && philo->params->philos_have_eaten == philo->params->even_half)
			{
				philo->params->turn++;
				philo->params->philos_have_eaten = 0;
			}
			printf("/MUTEX_UNLOCK ID[%d]\n", philo->id);
			pthread_mutex_unlock(&philo->fork);
			pthread_mutex_unlock(philo->fork_next);
		}
		usleep(500000);
		if (philo->meals == 3)
			return ((void *)philo);
	}
	return ((void *)philo);
}

int	launch(t_params *params)
{
	int	id;
		
	id = 0;
	while (++id <= params->num_of_philos)
	{
		if (pthread_create(&params->philo[id].thread, NULL, &test, &params->philo[id]))
			return (7);
		// printf("THREAD [%d] IS CREATED\n", id);
	}
	id = 0;
	while (++id <= params->num_of_philos)
	{
		if (pthread_join(params->philo[id].thread, NULL))
			return (8);
		// printf("THREAD [%d] IS FINISHED\n", id);
	}
	return (0);
}

// printf("num_of_philos = %d\ntime_to_die = %d\ntime_to_eat = %d\ntime_to_sleep = %d\ntimes_must_eat = %d\n",
// 		params->num_of_philos, params->time_to_die, params->time_to_eat, params->time_to_sleep, params->times_must_eat);

// void	*test(void *ptr)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)ptr;
// 	pthread_mutex_lock(&philo->fork);
// 	pthread_mutex_lock(philo->fork_next);
// 	printf("MUTEX_LOCK_UNLOCK ID[%d]\n", philo->id);
// 	pthread_mutex_unlock(&philo->fork);
// 	pthread_mutex_unlock(philo->fork_next);
// 	return ((void *)philo);
// }
