/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 04:48:21 by jgoldste          #+#    #+#             */
/*   Updated: 2022/05/05 03:15:06 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_init(t_params *params)
{
	int	id;

	id = 0;
	while (id < params->num_of_philos)
		if (pthread_mutex_init(&params->forks[id++], NULL))
			return (5);
	if (pthread_mutex_init(&params->print, NULL))
		return (5);
	return (0);
}

int	mutex_destroy(t_params *params)
{
	int	id;

	id = 0;
	while (id < params->num_of_philos)
		if (pthread_mutex_destroy(&params->forks[id++]))
			return (6);
	if (pthread_mutex_destroy(&params->print))
		return (6);
	return (0);
}

void	philos_init(t_params *params)
{
	int	id;

	id = 0;
	while (id < params->num_of_philos)
	{
		params->philo[id].id = id + 1;
		params->philo[id].meals = 0;
		params->philo[id].right_fork = id;
		if (id < params->num_of_philos - 1)
			params->philo[id].left_fork = id + 1;
		else
			params->philo[id].left_fork = 0;
		params->philo[id].params = params;
		id++;
	}
}
