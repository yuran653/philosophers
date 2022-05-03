/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 04:48:21 by jgoldste          #+#    #+#             */
/*   Updated: 2022/05/03 06:05:40 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_destroy(t_params *params)
{
	int	id;

	id = 0;
	while (++id <= params->num_of_philos)
		if (pthread_mutex_destroy(&params->philo[id].fork))
			return (6);
	if (pthread_mutex_destroy(&params->print))
		return (6);
	return (0);
}

int	philos_init(t_params *params)
{
	int	id;

	id = 0;
	while (++id <= params->num_of_philos)
	{
		params->philo[id].id = id;
		params->philo[id].meals = 0;
		if (pthread_mutex_init(&params->philo[id].fork, NULL))
			return (5);
		if (id < params->num_of_philos)// - 1)
		{
			if (pthread_mutex_init(&params->philo[id + 1].fork, NULL))
				return (5);
			params->philo[id].fork_next = &(params->philo[id + 1].fork);
		}
		else
			params->philo[id].fork_next = &(params->philo[0].fork);
		params->philo[id].params = params;
		// id++;
	}
	return (0);
}

// int	mutex_destroy(t_params *params)
// {
// 	int	id;

// 	id = 0;
// 	while (id < params->num_of_philos)
// 		if (pthread_mutex_destroy(&params->forks[id++]))
// 			return (6);
// 	return (0);
// }

// int	mutex_init(t_params *params)
// {
// 	int	id;

// 	id = 0;
// 	while (id < params->num_of_philos)
// 		if (pthread_mutex_init(&params->forks[id++], NULL))
// 			return (5);
// 	return (0);
// }

// void	philos_init(t_params *params)
// {
// 	int	id;

// 	id = 0;
// 	while (id < params->num_of_philos)
// 	{
// 		params->philo[id].id = id;
// 		params->philo[id].left_fork = id;
// 		if (id == 0)
// 			params->philo[id].right_fork = params->num_of_philos - 1;
// 		else
// 			params->philo[id].right_fork = id - 1;
// 		params->philo[id].params = params;
// 		id++;
// 	}
// }
