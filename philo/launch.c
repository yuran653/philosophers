/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 01:53:06 by jgoldste          #+#    #+#             */
/*   Updated: 2022/05/05 06:25:20 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	print_status(t_philo *philo, char *status)
// {
// 	t_params *params;

// 	params = philo->params;	
// 	pthread_mutex_lock(&params->print);
// 	printf("[%7lldms] philosopher[%03d] %s\n",
// 		// get_timestamp() - philo->start, philo->id, status);
// 		get_timestamp() - params->start, philo->id, status);
// 	pthread_mutex_unlock(&params->print);
// }

void	philo_is_sleeping(t_philo *philo, t_params *params)
{
	printf("[%7lums] philosopher[%03d] is sleeping\n", get_timestamp() - params->start, philo->id);
	ft_sleep(params->time_to_sleep, params);
}

void	philo_is_eating(t_philo *philo, t_params *params)
{
	pthread_mutex_lock(&params->forks[philo->right_fork]);
	printf("[%7lums] philosopher[%03d] has taken right fork\n", get_timestamp() - params->start, philo->id);
	pthread_mutex_lock(&params->forks[philo->left_fork]);
	printf("[%7lums] philosopher[%03d] has taken left fork\n", get_timestamp() - params->start, philo->id);
	printf("[%7lums] philosopher[%03d] is eating\n", get_timestamp() - params->start, philo->id);
	ft_sleep(params->time_to_eat - 1, params);
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
	// philo->start = get_timestamp();
	// while(params->start == -1)
	// 	usleep(200);
	printf("[%7lums] philosopher[%03d] is thinking\n", get_timestamp() - params->start, philo->id);
	if (philo->id % 2 == 0)
		// 	// usleep(15000);
			ft_sleep(philo->params->time_to_eat - 1, philo->params);
	while (1)
	{
		printf("[%7lums] philosopher[%03d] is thinking\n", get_timestamp() - params->start, philo->id);
		// if (philo->params->philo_is_dead)
		// 	return ((void *)philo);
		if (philo->meals == 1)
			return ((void *)philo);
		// if (philo->id % 2 == 0)
		// // 	// usleep(15000);
		// 	ft_sleep(philo->params->time_to_eat - 1, philo->params);
		philo_is_eating(philo, params);
		philo_is_sleeping(philo, params);
	}
	return ((void *)philo);
}

int	launch(t_params *params)
{
	int	id;
	t_philo	*philo;
		
	philo = params->philo;
	// params->start = -1;
	params->start = get_timestamp();
	id = 0;
	while (id < params->num_of_philos)
	{
		if (pthread_create(&params->thread[id], NULL, &philo_living, &philo[id]))
			return (7);
		// usleep(50);
		id++;
		// id += 2;
	}
	// params->start = get_timestamp();
	// pthread_mutex_unlock(&params->th);
	// ft_sleep(params->time_to_eat - 1, params);
	// id = 1;
	// while (id < params->num_of_philos)
	// {
	// 	if (pthread_create(&philo[id].thread, NULL, &philo_living, &philo[id]))
	// 		return (7);
	// 	usleep(50);
	// 	id += 2;
	// }
	id = 0;
	while (id < params->num_of_philos)
		if (pthread_join(params->thread[id++], NULL))
			return (8);
	return (0);
}

