/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:46:26 by jgoldste          #+#    #+#             */
/*   Updated: 2022/06/06 20:11:41 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	philo_is_living(t_philo *philo, t_params *params)
{
	print_status(philo, params, "is eating");
	ft_sleep(params->time_to_eat);
	sem_post(params->forks);
	sem_post(params->forks);
	philo->meals++;
	if (params->times_must_eat && params->times_must_eat == philo->meals)
	{
		sem_wait(params->print);
		printf("Philosofer [%03d] has eaten [%d] times\n", philo->id, philo->meals);
		sem_post(params->philos_had_eaten);
		sem_post(params->print);
	}
	print_status(philo, params, "is sleeping");
	ft_sleep(params->time_to_sleep);
	print_status(philo, params, "is thinking");
}

static void	philo_take_forks(t_philo *philo, t_params *params)
{
	long long	time_stamp;

	time_stamp = get_timestamp() - params->start;
	if (philo->death_time < time_stamp - params->start)
		exit (1);
	sem_wait(params->forks);
	print_status(philo, params, "has taken a fork");
	sem_wait(params->forks);
	print_status(philo, params, "has taken a fork");
	time_stamp = get_timestamp() - params->start;
	if (philo->death_time < time_stamp - params->start)
	{
		sem_post(params->forks);
		sem_post(params->forks);		
		exit (1);
	}
	philo->last_meal = time_stamp;
	philo->death_time = philo->last_meal + params->time_to_die;
	philo_is_living(philo, params);
}

void	philo_live(t_philo *philo, t_params *params)
{
	if (philo->id % 2)
	{
		print_status(philo, params, "is thinking");
		usleep((params->time_to_eat - 1) * 990);
	}
	while (1)
		philo_take_forks(philo, params);
}
