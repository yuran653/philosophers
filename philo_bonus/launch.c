/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 01:53:06 by jgoldste          #+#    #+#             */
/*   Updated: 2022/06/07 21:36:54 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	philo_died(t_philo *philo, t_params *params)
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

static void	*check_meals(void *ptr)
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
		philo_died(philo, params);
		usleep(50);
		id++;
	}
	return (NULL);
}

static int	thread_create_detach(pthread_t *th, void *func, t_params *params)
{
	if (pthread_create(th, NULL, func, params))
		return (7);
	if (pthread_detach(*th))
		return (7);
	return (0);
}

int	launch(t_philo *philo, t_params *params)
{
	pthread_t	stop_t;
	pthread_t	meals_t;
	int			id;

	id = 0;
	while (id < params->num_of_philos)
	{
		params->pid[id] = fork();
		if (params->pid[id] == -1)
			return (kill_all_processes(params, id, 6));
		if (params->pid[id] == 0)
		{
			philo->id = id + 1;
			if (params->times_must_eat && id == 0)
				if (thread_create_detach(&meals_t, &check_meals, params))
					return (kill_all_processes(params, id, 7));
			if (thread_create_detach(&stop_t, &death_check, params))
				return (kill_all_processes(params, id, 7));
			philo_live(philo, params);
		}
		usleep(50);
		id++;
	}
	wait_exit_status(params, id);
	return (0);
}

// printf("%lld %d died\n",
