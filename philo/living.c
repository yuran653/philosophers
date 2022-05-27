/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:46:26 by jgoldste          #+#    #+#             */
/*   Updated: 2022/05/28 00:13:01 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_is_living(t_philo *philo, t_params *params, long long time)
{
	philo->last_meal = time;
	pthread_mutex_lock(&philo->mut_death);
	philo->death_time = philo->last_meal + philo->time_to_die;
	pthread_mutex_unlock(&philo->mut_death);
	philo->meals++;
	if (print_status(philo, params, "is eating"))
		return (mutex_unlock_return_2(philo));
	if (ft_sleep(philo->time_to_eat, params))
		return (mutex_unlock_return_2(philo));
	pthread_mutex_unlock(&philo->forks->fork[philo->right_fork]);
	pthread_mutex_unlock(&philo->forks->fork[philo->left_fork]);
	if (print_status(philo, params, "is sleeping"))
		return (1);
	if (ft_sleep(philo->time_to_sleep, params))
		return (1);
	return (0);
}

static int	is_philo_dead(t_philo *philo, t_params *params, long long time)
{
	pthread_mutex_lock(&philo->mut_death);
	if (philo->death_time < time - params->start)
	{
		pthread_mutex_unlock(&philo->mut_death);
		pthread_mutex_lock(&params->death->mut);
		params->philo_is_dead = 1;
		pthread_mutex_unlock(&params->death->mut);
		return (1);
	}
	pthread_mutex_unlock(&philo->mut_death);
	pthread_mutex_lock(&params->death->mut);
	if (params->philo_is_dead == 1)
	{
		pthread_mutex_unlock(&params->death->mut);
		return (1);
	}
	pthread_mutex_unlock(&params->death->mut);
	return (0);
}

static int	philo_take_forks(t_philo *philo, t_params *params)
{
	long long	time_stamp;

	pthread_mutex_lock(&params->death->mut);
	if (params->philo_is_dead)
	{
		pthread_mutex_unlock(&params->death->mut);
		return (1);
	}
	pthread_mutex_unlock(&params->death->mut);
	pthread_mutex_lock(&philo->forks->fork[philo->right_fork]);
	if (print_status(philo, params, "has taken a fork"))
		return (mutex_unlock_return_1(philo));
	pthread_mutex_lock(&philo->forks->fork[philo->left_fork]);
	if (print_status(philo, params, "has taken a fork"))
		return (mutex_unlock_return_2(philo));
	time_stamp = get_timestamp() - philo->start;
	if (is_philo_dead(philo, params, time_stamp))
		return (mutex_unlock_return_2(philo));
	return (philo_is_living(philo, params, time_stamp));
}

static void	philo_is_thinking(t_philo *philo, t_params *params)
{
	print_status(philo, params, "is thinking");
	usleep((philo->time_to_eat - 1) * 990);
}

void	*philo_live(void *ptr)
{
	t_philo		*philo;
	t_params	*params;

	philo = (t_philo *)ptr;
	params = philo->params;
	if (philo->id % 2 == 0)
		philo_is_thinking(philo, params);
	while (1)
	{
		pthread_mutex_lock(&params->death->mut);
		if (params->philo_is_dead)
		{
			pthread_mutex_unlock(&params->death->mut);
			return (NULL);
		}
		pthread_mutex_unlock(&params->death->mut);
		if (philo->times_must_eat)
			if (philo->times_must_eat == philo->meals)
				return (NULL);
		if (philo_take_forks(philo, params))
			return (NULL);
		if (print_status(philo, params, "is thinking"))
			return (NULL);
	}
	return (NULL);
}