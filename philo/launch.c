/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 01:53:06 by jgoldste          #+#    #+#             */
/*   Updated: 2022/05/28 00:10:12 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_is_died(t_philo *philo, t_params *params, int id)
{
	long long	time;

	time = get_timestamp();
	if (philo[id].death_time < time - philo[id].start)
	{
		pthread_mutex_unlock(&philo[id].mut_death);
		pthread_mutex_lock(&params->death->mut);
		params->philo_is_dead = 1;
		pthread_mutex_unlock(&params->death->mut);
		pthread_mutex_lock(&params->print->mut);
		printf("\t[%7lldms] philosopher [%3d] is died\n",
			time - params->start, philo[id].id);
		return (1);
	}
	return (0);
}

static void	*death_check(void *ptr)
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
		pthread_mutex_lock(&philo[id].mut_death);
		if (philo_is_died(philo, params, id))
			return (NULL);
		pthread_mutex_unlock(&philo[id].mut_death);
		usleep(50);
		id++;
	}
	return (NULL);
}

static int	create_threads(pthread_t *th, t_philo *philo, int num, int id)
{
	while (id < num)
	{
		if (pthread_create(&th[id], NULL, &philo_live, &philo[id]))
			return (7);
		id += 2;
		usleep(10);
	}
	return (0);
}

int	launch(t_params *params)
{
	t_philo		*philo;
	pthread_t	*th;
	pthread_t	death_t;
	int			num;
	int			id;

	philo = params->philo;
	th = params->thread;
	num = params->num_of_philos;
	if (create_threads(th, philo, num, 0) || create_threads(th, philo, num, 1))
		return (7);
	if (pthread_create(&death_t, NULL, &death_check, params))
		return (7);
	if (pthread_join(death_t, NULL))
		return (8);
	if (params->num_of_philos == 1)
		pthread_mutex_unlock(&philo->forks->fork[philo->right_fork]);
	pthread_mutex_unlock(&params->print->mut);
	id = 0;
	while (id < params->num_of_philos)
		if (pthread_join(params->thread[id++], NULL))
			return (8);
	return (0);
}
