/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 01:53:06 by jgoldste          #+#    #+#             */
/*   Updated: 2022/05/04 05:46:57 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_is_sleeping(t_philo *philo, t_params *params)
{
	print_status(philo, "is sleeping");
	ft_sleep(params->time_to_sleep, params);
}

void	philo_is_eating(t_philo *philo, t_params *params)
{
	pthread_mutex_lock(&params->forks[philo->right_fork]);
	print_status(philo, "has taken fork");
	pthread_mutex_lock(&params->forks[philo->left_fork]);
	print_status(philo, "has taken fork");
	print_status(philo, "is eating");
	ft_sleep(params->time_to_eat, params);
	philo->meals++;
	pthread_mutex_unlock(&params->forks[philo->right_fork]);
	pthread_mutex_unlock(&params->forks[philo->left_fork]);
}

void	*philo_living(void *ptr)
{
	t_philo		*philo;
	t_params	*params;
	
	philo = (t_philo *)ptr;
	params = (t_params *)philo->params;
	philo->start = get_timestamp();
	while (1)
	{
		if (philo->params->philo_is_dead)
			return ((void *)philo);
		if (philo->meals == 5)
			return ((void *)philo);
		if (philo->id % 2 == 0)
			usleep(15000);//ft_sleep(philo->params->time_to_eat - 1, philo->params);
		philo_is_eating(philo, params);
		philo_is_sleeping(philo, params);
		// philo_is_thinking(philo);
	}
	return ((void *)philo);
}

int	launch(t_params *params)
{
	int	id;
		
	// params->start = get_timestamp();
	id = 0;
	while (id < params->num_of_philos)
	{
		if (pthread_create(&params->philo[id].thread, NULL, &philo_living, &params->philo[id]))
			return (7);
		id++;
		// id += 2;
	}
	// ft_sleep(params->time_to_eat - 1, params);
	// id = 1;
	// while (id < params->num_of_philos)
	// {
	// 	if (pthread_create(&params->philo[id].thread, NULL, &philo_living, &params->philo[id]))
	// 		return (7);
	// 	id += 2;
	// }
	id = 0;
	while (id < params->num_of_philos)
		if (pthread_join(params->philo[id++].thread, NULL))
			return (8);
	return (0);
}

