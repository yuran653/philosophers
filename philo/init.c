/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 04:48:21 by jgoldste          #+#    #+#             */
/*   Updated: 2022/05/30 13:39:56 by jgoldste         ###   ########.fr       */
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
	id = 0;
	while (id < params->num_of_philos)
		if (pthread_mutex_init(&params->philo[id++].mut_death, NULL))
			return (5);
	if (pthread_mutex_init(&params->print->mut, NULL))
		return (5);
	if (pthread_mutex_init(&params->exit->mut, NULL))
		return (5);
	if (pthread_mutex_init(&params->meals_mut->mut, NULL))
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
	id = 0;
	while (id < params->num_of_philos)
		if (pthread_mutex_destroy(&params->philo[id++].mut_death))
			return (6);
	if (pthread_mutex_destroy(&params->print->mut))
		return (6);
	if (pthread_mutex_destroy(&params->exit->mut))
		return (6);
	if (pthread_mutex_destroy(&params->meals_mut->mut))
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
		params->philo[id].left_fork = 0;
		if (id < params->num_of_philos - 1)
			params->philo[id].left_fork = id + 1;
		params->philo[id].death_time = params->time_to_die;
		params->philo[id].last_meal = params->start;
		params->philo[id].start = params->start;
		params->philo[id].forks = params->forks;
		params->philo[id].print = params->print;
		params->philo[id].meals_mut = params->meals_mut;
		params->philo[id].params = params;
		id++;
	}
}

static int	malloc_mutex(t_params *params)
{
	t_print	*print;
	t_exit	*exit;
	t_meals	*meals_mut;

	print = (t_print *)malloc(sizeof(t_print));
	if (!print)
		return (4);
	params->print = print;
	exit = (t_exit *)malloc(sizeof(t_exit));
	if (!exit)
		return (4);
	params->exit = exit;
	meals_mut = (t_meals *)malloc(sizeof(t_meals));
	if (!meals_mut)
		return (4);
	params->meals_mut = meals_mut;
	return (0);
}

int	malloc_arrays(t_params *params, int size)
{
	t_forks	*forks;

	params->philo = (t_philo *)malloc(sizeof(t_philo) * size);
	if (!params->philo)
		return (4);
	forks = (t_forks *)malloc(sizeof(t_forks) * size);
	if (!forks)
		return (4);
	params->forks = forks;
	forks->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * size);
	if (!forks->fork)
		return (4);
	params->thread = (pthread_t *)malloc(sizeof(pthread_t) * size);
	if (!params->thread)
		return (4);
	if (malloc_mutex(params))
		return (4);
	return (0);
}
