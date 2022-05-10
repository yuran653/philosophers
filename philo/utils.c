/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:24:43 by jgoldste          #+#    #+#             */
/*   Updated: 2022/05/10 20:13:16 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_null(void *ptr)
{
	free(ptr);
	ptr = NULL;
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
		if (params->philo_is_dead)
			return (1);
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
