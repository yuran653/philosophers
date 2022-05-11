/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:46:26 by jgoldste          #+#    #+#             */
/*   Updated: 2022/05/11 18:17:46 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_actions(t_philo *philo, t_params *params, int time_stamp)
{
	philo->last_meal = time_stamp;
	philo->death_time = philo->last_meal + philo->time_to_die;
	philo->meals++;
	if (print_status(philo, params, "is eating"))
		return (mutex_unlock_return_2(&philo->forks->fork[philo->right_fork],
				&philo->forks->fork[philo->left_fork]));
	if (ft_sleep(philo->time_to_eat, params))
		return (mutex_unlock_return_2(&philo->forks->fork[philo->right_fork],
				&philo->forks->fork[philo->left_fork]));
	pthread_mutex_unlock(&philo->forks->fork[philo->right_fork]);
	pthread_mutex_unlock(&philo->forks->fork[philo->left_fork]);
	if (print_status(philo, params, "is sleeping"))
		return (1);
	if (ft_sleep(philo->time_to_sleep, params))
		return (1);
	return (0);
}

static int	philo_take_forks(t_philo *philo, t_params *params)
{
	long long	time_stamp;

	if (params->philo_is_dead)
		return (1);
	pthread_mutex_lock(&philo->forks->fork[philo->right_fork]);
	if (print_status(philo, params, "has taken a fork"))
		return (mutex_unlock_return_1(&philo->forks->fork[philo->right_fork]));
	pthread_mutex_lock(&philo->forks->fork[philo->left_fork]);
	if (print_status(philo, params, "has taken a fork"))
		return (mutex_unlock_return_2(&philo->forks->fork[philo->right_fork],
				&philo->forks->fork[philo->left_fork]));
	time_stamp = get_timestamp() - philo->start;
	if (philo->death_time < time_stamp - params->start)
	{
		params->philo_is_dead = 1;
		return (mutex_unlock_return_2(&philo->forks->fork[philo->right_fork],
				&philo->forks->fork[philo->left_fork]));
	}
	return (philo_actions(philo, params, time_stamp));
}

void	*philo_live(void *ptr)
{
	t_philo		*philo;
	t_params	*params;

	philo = (t_philo *)ptr;
	params = philo->params;
	if (philo->id % 2 == 0)
	{
		print_status(philo, params, "is thinking");
		usleep((philo->time_to_eat - 1) * 990);
	}
	while (1)
	{
		if (params->philo_is_dead)
			return (NULL);
		if (philo->times_must_eat)
			if (philo->meals == philo->times_must_eat)
				return (NULL);
		if (philo_take_forks(philo, params))
			return (NULL);
		if (print_status(philo, params, "is thinking"))
			return (NULL);
	}
	return (NULL);
}
