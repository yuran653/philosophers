/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 06:29:25 by jgoldste          #+#    #+#             */
/*   Updated: 2022/06/01 06:29:26 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// int	print_status(t_philo *philo, t_params *params, char *action)
// {
// 	pthread_mutex_lock(&params->print->mut);
// 	pthread_mutex_lock(&params->exit->mut);
// 	if (!params->philo_exit)
// 	{
// 		pthread_mutex_unlock(&params->exit->mut);
// 		printf("\t[%7lldms] philosopher [%3d] %s\n",
// 			get_timestamp() - philo->start, philo->id, action);
// 		pthread_mutex_unlock(&params->print->mut);
// 		return (0);
// 	}
// 	pthread_mutex_unlock(&params->print->mut);
// 	pthread_mutex_unlock(&params->exit->mut);
// 	return (1);
// }

long long	get_timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

// int	ft_sleep(long long m_secs, t_params *params)
// {
// 	long long	stop;

// 	stop = get_timestamp() + m_secs;
// 	while (get_timestamp() < stop)
// 	{
// 		pthread_mutex_lock(&params->exit->mut);
// 		if (params->philo_exit)
// 		{
// 			pthread_mutex_unlock(&params->exit->mut);
// 			return (1);
// 		}
// 		pthread_mutex_unlock(&params->exit->mut);
// 		usleep(500);
// 	}
// 	return (0);
// }

// printf("%lld %d %s\n",
