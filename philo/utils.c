/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:24:43 by jgoldste          #+#    #+#             */
/*   Updated: 2022/05/06 23:59:02 by jgoldste         ###   ########.fr       */
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

int	ft_sleep(size_t m_secs, t_params *params)
{
	size_t	start;

	start = get_timestamp();
	while (get_timestamp() - start < m_secs)
	{
		if (params->philo_is_dead)
			return (1);
		usleep(100);
	}
	return (0);
}
