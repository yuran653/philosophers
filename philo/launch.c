/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 01:53:06 by jgoldste          #+#    #+#             */
/*   Updated: 2022/05/06 05:51:45 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void	philo_is_sleeping(t_philo *philo, t_params *params)
// {
// 	pthread_mutex_lock(&params->print);
// 	printf("[%7lldms] philosopher [%3d] is sleeping\n",
// 		get_timestamp() - philo->start, philo->id);
// 	pthread_mutex_unlock(&params->print);
// 	ft_sleep(params->time_to_sleep, params);
// 	(void) params;
// }

static void	philo_is_eating(t_philo *philo, t_params *params)
{
	// pthread_mutex_lock(&params->print);
	pthread_mutex_lock(&params->forks[philo->right_fork]);
	// pthread_mutex_lock(&params->print);
	printf("[%7lldms] philosopher [%3d] has taken rigth fork [%3d]\n",
		get_timestamp() - philo->start, philo->id, philo->right_fork);
	// pthread_mutex_unlock(&params->print);
	pthread_mutex_lock(&params->forks[philo->left_fork]);
	// pthread_mutex_lock(&params->print);
	printf("[%7lldms] philosopher [%3d] has taken  left fork [%3d]\n",
		get_timestamp() - philo->start, philo->id, philo->left_fork);
	// pthread_mutex_unlock(&params->print);
	philo->last_meal = get_timestamp();
	// pthread_mutex_lock(&params->print);
	// printf("[%7lldms] philosopher [%3d] is eating\n",
	// 	philo->last_meal - philo->start, philo->id);
	// pthread_mutex_unlock(&params->print);
	philo->meals++;
	ft_sleep(params->time_to_eat, params);
	pthread_mutex_unlock(&params->forks[philo->right_fork]);
	pthread_mutex_unlock(&params->forks[philo->left_fork]);	
}

static void	*philo_live(void *ptr)
{
	t_philo		*philo;
	t_params	*params;
	
	philo = (t_philo *)ptr;
	params = philo->params;
	// if (philo->id % 2 == 0)
	// {
	// 	printf("[%7lldms] philosopher [%3d] is thinking\n",
	// 		get_timestamp() - philo->start, philo->id);
	// 	ft_sleep(params->time_to_eat, params);
	// }
	while (!params->philo_is_dead)
	{
		if (philo->meals == params->times_must_eat)
			return (NULL);
		philo_is_eating(philo, params);
		// philo_is_sleeping(philo, params);
		// pthread_mutex_lock(&params->print);
		// printf("[%7lldms] philosopher [%3d] is sleeping\n",
		// 	get_timestamp() - philo->start, philo->id);
		// pthread_mutex_unlock(&params->print);
		ft_sleep(params->time_to_sleep, params);
		// pthread_mutex_lock(&params->print);
		// printf("[%7lldms] philosopher [%3d] is thinking\n",
		// 	get_timestamp() - philo->start, philo->id);
		// pthread_mutex_unlock(&params->print);
	}
	return (NULL);
}

void	*empty(void *ptr)
{
	(void) ptr;
	return (NULL);
}

int	launch(t_params *params)
{
	t_philo	*philo;
	int		id;

	philo = params->philo;
	id = 0;
	while(id < params->num_of_philos)
	{
		if (pthread_create(&params->thread[id], NULL, &philo_live, &philo[id]))
			return (7);
		// usleep(250);
		id += 2;
		// id++;
	}
	ft_sleep(params->time_to_eat, params);
	id = 1;
	while (id < params->num_of_philos)
	{
		if (pthread_create(&params->thread[id], NULL, &empty, NULL))
		// if (pthread_create(&params->thread[id], NULL, &philo_live, &philo[id]))
			return (7);
		usleep(250);
		id += 2;
	}
	id = 0;
	while (id < params->num_of_philos)
		if (pthread_join(params->thread[id++], NULL))
			return (8);
	return (0);
}
