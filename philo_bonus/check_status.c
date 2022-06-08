/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:18:45 by jgoldste          #+#    #+#             */
/*   Updated: 2022/06/08 16:19:39 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_died(t_philo *philo, t_params *params)
{
	long long	time;

	time = get_timestamp();
	if (philo->death_time < time - params->start)
	{
		sem_wait(params->print);
		printf("\t[%7lldms] philosopher [%3d] died\n",
			time - params->start, philo->id);
		exit (1);
	}
}

void	*death_check(void *ptr)
{
	t_params	*params;
	t_philo		*philo;
	int			id;

	params = (t_params *)ptr;
	philo = params->philo;
	id = 0;
	while (id <= params->num_of_philos)
	{
		if (id == params->num_of_philos)
			id = 0;
		philo_died(philo, params);
		usleep(50);
		id++;
	}
	return (NULL);
}

void	*check_meals(void *ptr)
{
	t_params	*params;
	int			i;

	params = (t_params *)ptr;
	i = 0;
	sem_wait(params->philos_had_eaten);
	while (i++ < params->num_of_philos)
		sem_wait(params->philos_had_eaten);
	sem_wait(params->print);
	exit (1);
	return (NULL);
}
