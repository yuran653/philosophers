/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:24:43 by jgoldste          #+#    #+#             */
/*   Updated: 2022/05/28 00:00:42 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_unlock_return_1(t_philo *philo)
{
	pthread_mutex_unlock(&philo->forks->fork[philo->right_fork]);
	return (1);
}

int	mutex_unlock_return_2(t_philo *philo)
{
	pthread_mutex_unlock(&philo->forks->fork[philo->right_fork]);
	pthread_mutex_unlock(&philo->forks->fork[philo->left_fork]);
	return (1);
}

int	print_status(t_philo *philo, t_params *params, char *action)
{
	pthread_mutex_lock(&params->death->mut);
	if (!params->philo_is_dead)
	{
		pthread_mutex_unlock(&params->death->mut);
		pthread_mutex_lock(&params->death->mut);
		if (params->philo_is_dead)
		{
			pthread_mutex_unlock(&params->death->mut);
			return (1);
		}
		pthread_mutex_unlock(&params->death->mut);
		pthread_mutex_lock(&params->print->mut);
		printf("\t[%7lldms] philosopher [%3d] %s\n",
			get_timestamp() - philo->start, philo->id, action);
		pthread_mutex_unlock(&params->print->mut);
		return (0);
	}
	pthread_mutex_unlock(&params->death->mut);
	return (1);
}

long long	get_timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	ft_sleep(long long m_secs, t_params *params)
{
	long long	stop;

	stop = get_timestamp() + m_secs;
	while (get_timestamp() < stop)
	{
		pthread_mutex_lock(&params->death->mut);
		if (params->philo_is_dead)
		{
			pthread_mutex_unlock(&params->death->mut);
			return (1);
		}
		pthread_mutex_unlock(&params->death->mut);
		usleep(500);
	}
	return (0);
}

// int	ft_sleep(long long m_secs, t_params *params)
// {
// 	long long	start;

// 	start = get_timestamp();
// 	while (get_timestamp() < start + m_secs)
// 	{
// 		if (params->philo_is_dead)
// 			return (1);
// 		usleep(250);
// 	}
// 	return (0);
// }
