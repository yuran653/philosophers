/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 01:53:06 by jgoldste          #+#    #+#             */
/*   Updated: 2022/05/11 12:52:32 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_action(t_philo *philo, t_params *params)
{
	if (params->philo_is_dead)
		return (1);
	pthread_mutex_lock(&philo->forks->fork[philo->right_fork]);
	if (print_status(philo, params, "has taken the right fork"))
		return (mutex_unlock_return_1(&philo->forks->fork[philo->right_fork]));
	pthread_mutex_lock(&philo->forks->fork[philo->left_fork]);
	if (print_status(philo, params, "has taken the left fork"))
		return (mutex_unlock_return_2(&philo->forks->fork[philo->right_fork],
				&philo->forks->fork[philo->left_fork]));
	philo->last_meal = get_timestamp() - philo->start;
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

static void	*philo_live(void *ptr)
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
		if (philo_action(philo, params))
			return (NULL);
		if (print_status(philo, params, "is thinking"))
			return (NULL);
	}
	return (NULL);
}

static void	*death_check(void *ptr)
{
	t_params	*params;
	t_philo		*philo;
	long long	time;
	int			id;

	params = (t_params *)ptr;
	philo = params->philo;
	id = 0;
	while (id <= params->num_of_philos)
	{
		if (id == params->num_of_philos)
			id = 0;
		time = get_timestamp();
		if (philo[id].death_time < time - params->start)
		{
			params->philo_is_dead = 1;
			pthread_mutex_lock(&params->print->mut);
			printf("[%7lldms] philosopher [%3d] is died\n",
				time - params->start, id++);
			return (NULL);
		}
		usleep(50);
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
	id = 0;
	while (id < params->num_of_philos)
		if (pthread_join(params->thread[id++], NULL))
			return (8);
	pthread_mutex_unlock(&params->print->mut);
	return (0);
}
