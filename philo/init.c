/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 04:48:21 by jgoldste          #+#    #+#             */
/*   Updated: 2022/05/08 05:25:29 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_init(t_params *params)
{
	int	id;

	id = 0;
	while (id < params->num_of_philos)
		if (pthread_mutex_init(&params->forks->fork[id++], NULL))
			return (5);
	if (pthread_mutex_init(&params->print->mut, NULL))
		return (5);
	return (0);
}

int	mutex_destroy(t_params *params)
{
	int	id;

	id = 0;
	while (id < params->num_of_philos)
		if (pthread_mutex_destroy(&params->forks->fork[id++]))
			return (6);
	if (pthread_mutex_destroy(&params->print->mut))
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
		params->philo[id].time_to_die = params->time_to_die;
		params->philo[id].time_to_eat = params->time_to_eat;
		params->philo[id].time_to_sleep = params->time_to_sleep;
		params->philo[id].times_must_eat = params->times_must_eat;
		params->philo[id].right_fork = id;
		if (id < params->num_of_philos - 1)
			params->philo[id].left_fork = id + 1;
		else
			params->philo[id].left_fork = 0;
		params->philo[id].start = params->start;
		params->philo[id].forks = params->forks;
		params->philo[id].print = params->print;
		params->philo[id].params = params;
		id++;
	}
}

int	malloc_arrays(t_params *params)
{
	t_forks	*forks;
	t_print	*print;
	
	params->philo = (t_philo *)malloc(sizeof(t_philo) * params->num_of_philos);
	if (!params->philo)
		return (4);
	forks = (t_forks *)malloc(sizeof(t_forks));
	if (!forks)
		return (4);
	forks->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * params->num_of_philos);
	if (!forks->fork)
		return (4);
	params->forks = forks;
	print = (t_print *)malloc(sizeof(t_print));
	if (!print)
		return (4);
	params->print = print;
	params->thread = (pthread_t *)malloc(sizeof(pthread_t)
			* params->num_of_philos);
	if (!params->thread)
		return (4);
	return (0);
}
