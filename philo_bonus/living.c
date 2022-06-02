/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:46:26 by jgoldste          #+#    #+#             */
/*   Updated: 2022/06/02 06:54:29 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// static int	philo_is_living(t_philo *philo, t_params *params)
// {
// 	if (print_status(philo, params, "is eating"))
// 		return (mutex_unlock_return_2(philo));
// 	if (ft_sleep(philo->time_to_eat, params))
// 		return (mutex_unlock_return_2(philo));
// 	pthread_mutex_unlock(&philo->forks->fork[philo->right_fork]);
// 	pthread_mutex_unlock(&philo->forks->fork[philo->left_fork]);
// 	philo->meals++;
// 	if (philo->times_must_eat && philo->times_must_eat == philo->meals)
// 	{
// 		pthread_mutex_lock(&philo->meals_mut->mut);
// 		params->philos_had_eaten++;
// 		pthread_mutex_unlock(&philo->meals_mut->mut);
// 	}
// 	if (print_status(philo, params, "is sleeping"))
// 		return (1);
// 	if (ft_sleep(philo->time_to_sleep, params))
// 		return (1);
// 	return (0);
// }

// static int	is_philo_dead(t_philo *philo, t_params *params, long long time)
// {
// 	pthread_mutex_lock(&philo->mut_death);
// 	if (philo->death_time < time - params->start)
// 	{
// 		pthread_mutex_unlock(&philo->mut_death);
// 		pthread_mutex_lock(&params->exit->mut);
// 		params->philo_exit = 1;
// 		pthread_mutex_unlock(&params->exit->mut);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&philo->mut_death);
// 	pthread_mutex_lock(&params->exit->mut);
// 	if (params->philo_exit == 1)
// 	{
// 		pthread_mutex_unlock(&params->exit->mut);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&params->exit->mut);
// 	philo->last_meal = time;
// 	pthread_mutex_lock(&philo->mut_death);
// 	philo->death_time = philo->last_meal + philo->time_to_die;
// 	pthread_mutex_unlock(&philo->mut_death);
// 	return (0);
// }

// static int	philo_take_forks(t_philo *philo, t_params *params)
// {
// 	long long	time_stamp;

// 	pthread_mutex_lock(&params->exit->mut);
// 	if (params->philo_exit)
// 	{
// 		pthread_mutex_unlock(&params->exit->mut);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&params->exit->mut);
// 	pthread_mutex_lock(&philo->forks->fork[philo->right_fork]);
// 	if (print_status(philo, params, "has taken a fork"))
// 		return (mutex_unlock_return_1(philo));
// 	pthread_mutex_lock(&philo->forks->fork[philo->left_fork]);
// 	if (print_status(philo, params, "has taken a fork"))
// 		return (mutex_unlock_return_2(philo));
// 	time_stamp = get_timestamp() - philo->start;
// 	if (is_philo_dead(philo, params, time_stamp))
// 		return (mutex_unlock_return_2(philo));
// 	return (philo_is_living(philo, params));
// }

// void	*philo_live(void *ptr)
// {
// 	t_philo		*philo;
// 	t_params	*params;

// 	philo = (t_philo *)ptr;
// 	params = philo->params;
// 	if (philo->id % 2 != 0)
// 	{
// 		print_status(philo, params, "is thinking");
// 		usleep((philo->time_to_eat - 1) * 990);
// 	}
// 	while (1)
// 	{
// 		pthread_mutex_lock(&params->exit->mut);
// 		if (params->philo_exit)
// 		{
// 			pthread_mutex_unlock(&params->exit->mut);
// 			return (NULL);
// 		}
// 		pthread_mutex_unlock(&params->exit->mut);
// 		if (philo_take_forks(philo, params))
// 			return (NULL);
// 		if (print_status(philo, params, "is thinking"))
// 			return (NULL);
// 	}
// 	return (NULL);
// }

int	philo_live(t_philo *philo, t_params *params)
{
	sem_wait(params->print);
	printf("Philosofer [%d] time to die -> [%lld]\n", philo->id, philo->death_time - params->start);
	sem_post(params->print);
	return (0);
}
