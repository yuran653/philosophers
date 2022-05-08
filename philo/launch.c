/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 01:53:06 by jgoldste          #+#    #+#             */
/*   Updated: 2022/05/08 05:58:34 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_action(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks->fork[philo->right_fork]);
	printf("[%7lldms] philosopher [%3d] has taken a fork\n",
		get_timestamp() - philo->start, philo->id);
	pthread_mutex_lock(&philo->forks->fork[philo->left_fork]);
	printf("[%7lldms] philosopher [%3d] has taken a fork\n",
		get_timestamp() - philo->start, philo->id);
	philo->last_meal = get_timestamp();
	printf("[%7lldms] philosopher [%3d] is eating\n",
		philo->last_meal - philo->start, philo->id);
	philo->meals++;
	ft_sleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->forks->fork[philo->right_fork]);
	pthread_mutex_unlock(&philo->forks->fork[philo->left_fork]);	
}

static void	*philo_live(void *ptr)
{
	t_philo		*philo;
	t_params	*params;
	
	philo = (t_philo *)ptr;
	params = philo->params;
	if (philo->id % 2 == 0)
	{
		printf("[%7lldms] philosopher [%3d] is thinking\n",
			get_timestamp() - philo->start, philo->id);
		ft_sleep(params->time_to_eat - 1);
	}
	while (!params->philo_is_dead)
	{
		printf("[%7lldms] philosopher [%3d] is thinking\n",
			get_timestamp() - philo->start, philo->id);
		if (philo->meals == philo->times_must_eat)
			return (NULL);
		philo_action(philo);
		printf("[%7lldms] philosopher [%3d] is sleeping\n",
			get_timestamp() - philo->start, philo->id);
		ft_sleep(philo->time_to_sleep);
	}
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
		usleep(10);
		// id += 2;
		id++;
	}
	id = 0;
	while (id < params->num_of_philos)
		if (pthread_join(params->thread[id++], NULL))
			return (8);
	return (0);
}
