/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 01:53:06 by jgoldste          #+#    #+#             */
/*   Updated: 2022/06/02 06:55:49 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// static int	philo_died(t_philo *philo, t_params *params, int id)
// {
// 	long long	time;

// 	time = get_timestamp();
// 	if (philo[id].death_time < time - philo[id].start)
// 	{
// 		pthread_mutex_unlock(&philo[id].mut_death);
// 		pthread_mutex_lock(&params->stop->mut);
// 		params->philo_exit = 1;
// 		pthread_mutex_unlock(&params->stop->mut);
// 		pthread_mutex_lock(&params->print->mut);
// 		printf("\t[%7lldms] philosopher [%3d] died\n",
// 			time - params->start, philo[id].id);
// 		return (1);
// 	}
// 	return (0);
// }

// static int	check_philos_had_eaten(t_philo *philo, t_params *params)
// {
// 	pthread_mutex_lock(&philo->meals_mut->mut);
// 	if (params->philos_had_eaten == params->num_of_philos)
// 	{
// 		pthread_mutex_lock(&params->stop->mut);
// 		params->philo_exit = 1;
// 		pthread_mutex_unlock(&params->stop->mut);
// 		pthread_mutex_unlock(&philo->meals_mut->mut);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&philo->meals_mut->mut);
// 	return (0);
// }

// static void	*death_meals_check(void *ptr)
// {
// 	t_params	*params;
// 	t_philo		*philo;
// 	int			id;

// 	params = (t_params *)ptr;
// 	philo = params->philo;
// 	id = 0;
// 	while (id <= params->num_of_philos)
// 	{
// 		if (id == params->num_of_philos)
// 		{
// 			id = 0;
// 			if (check_philos_had_eaten(philo, params))
// 				return (NULL);
// 		}
// 		pthread_mutex_lock(&philo[id].mut_death);
// 		if (philo_died(philo, params, id))
// 			return (NULL);
// 		pthread_mutex_unlock(&philo[id].mut_death);
// 		usleep(50);
// 		id++;
// 	}
// 	return (NULL);
// }

int	launch(t_philo *philo, t_params *params)
{
	// pthread_t	death_t;
	int		status;	
	int		id;

	id = 0;
	while (id < params->num_of_philos)
	{
		params->pid[id] = fork();
		if (params->pid[id] == -1)
			return (7);
		if (params->pid[id] == 0)
		{
			philo->id = id + 1;
			if (philo_live(philo, params))
				return (0);
		}
		id++;
	}
	waitpid(-1, &status, 0);
	// if (pthread_create(&death_t, NULL, &death_meals_check, params))
	// 	return (7);
	// if (pthread_join(death_t, NULL))
	// 	return (8);
	// if (params->num_of_philos == 1)
	// 	pthread_mutex_unlock(&philo->forks->fork[philo->right_fork]);
	// pthread_mutex_unlock(&params->print->mut);
	// id = 0;
	// while (id < params->num_of_philos)
	// 	if (pthread_join(params->thread[id++], NULL))
	// 		return (8);
	
	return (0);
}

// printf("%lld %d died\n",
