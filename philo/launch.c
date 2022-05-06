/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 01:53:06 by jgoldste          #+#    #+#             */
/*   Updated: 2022/05/07 00:18:43 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	print_status(t_philo *philo, t_params *params, char *action)
{
	if (params->philo_is_dead)
		return (1);
	pthread_mutex_lock(&params->print);
	printf("[%7lldms] philosopher [%3d] %s\n",
		get_timestamp() - philo->start, philo->id, action);
		// get_timestamp() - time, id, action);
	pthread_mutex_unlock(&params->print);
	return (0);
}

static int	philo_action(t_philo *philo, t_params *params)
{
	pthread_mutex_lock(&philo->forks->fork[philo->right_fork]);
	if (print_status(philo, params, "has taken a fork"))
		return (1);
	// if (print_status(philo->start, philo->id, "has taken a fork",
	// 		params->philo_is_dead))
	// 	return (1);
	pthread_mutex_lock(&philo->forks->fork[philo->left_fork]);
	if (print_status(philo, params, "has taken a fork"))
		return (1);
	// if (print_status(philo->start, philo->id, "has taken a fork",
	// 		params->philo_is_dead))
	// 	return (1);
	philo->last_meal = get_timestamp();
	if (print_status(philo, params, "is eating"))
		return (1);
	// if (print_status(philo->start, philo->id, "is eating",
	// 		params->philo_is_dead))
	// 	return (1);
	philo->meals++;
	ft_sleep(philo->time_to_eat, params);
	pthread_mutex_unlock(&philo->forks->fork[philo->right_fork]);
	pthread_mutex_unlock(&philo->forks->fork[philo->left_fork]);
	if (print_status(philo, params, "is sleeping"))
		return (1);
	// if (print_status(philo->start, philo->id, "is sleeping",
	// 		params->philo_is_dead))
	// 	return (1);
	ft_sleep(philo->time_to_sleep, params);
	return (0);
}

static void	*philo_live(void *ptr)
{
	t_philo		*philo;
	t_params	*params;

	philo = (t_philo *)ptr;
	params = philo->params;
	pthread_mutex_lock(&params->print);
	printf("[%7lldms] philosopher [%3d] is thinking\n",
		get_timestamp() - philo->start, philo->id);
	pthread_mutex_unlock(&params->print);
	if (philo->id % 2 == 0)
		ft_sleep(philo->time_to_eat - 1, params);
	while (!params->philo_is_dead)
	{
		if (philo->meals == philo->times_must_eat)
			return (NULL);
		if (philo_action(philo, params))
			return (NULL);
		if (params->philo_is_dead)
			return (NULL);
		pthread_mutex_lock(&params->print);
		printf("[%7lldms] philosopher [%3d] is thinking\n",
			get_timestamp() - philo->start, philo->id);
		pthread_mutex_unlock(&params->print);
	}
	return (NULL);
}

int	launch(t_params *params)
{
	t_philo	*philo;
	int		id;

	philo = params->philo;
	id = 0;
	while (id < params->num_of_philos)
	{
		if (pthread_create(&params->thread[id], NULL, &philo_live, &philo[id]))
			return (7);
		usleep(50);
		id++;
	}
	id = 0;
	while (id < params->num_of_philos)
		if (pthread_join(params->thread[id++], NULL))
			return (8);
	return (0);
}
