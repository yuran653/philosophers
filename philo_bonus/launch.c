/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 01:53:06 by jgoldste          #+#    #+#             */
/*   Updated: 2022/06/09 21:17:40 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	thread_create_detach(pthread_t *th, void *func, t_params *params)
{
	if (pthread_create(th, NULL, func, params))
		return (7);
	if (pthread_detach(*th))
		return (7);
	return (0);
}

static int	create_process(t_philo *philo, t_params *params, int id)
{
	pthread_t	stop_t;
	pthread_t	meals_t;

	if (params->times_must_eat && id == 0)
		if (thread_create_detach(&meals_t, &check_meals, params))
			return (7);
	if (thread_create_detach(&stop_t, &death_check, params))
		return (7);
	philo_live(philo, params);
	return (0);
}

void	init_sem_name(int id, char *name)
{
	int		i;

	i = 4;
	name[i] = 'S';
	while (--i > 0)
	{
		name[i] = id % 10 + 48;
		id = id / 10;
	}
	name[i] = '/';
}

int	launch(t_philo *philo, t_params *params)
{
	int			id;

	params->start = get_timestamp();
	philo->last_meal = params->start;
	id = -1;
	while (++id < params->num_of_philos)
	{
		philo->id = id + 1;
		params->pid[id] = fork();
		if (params->pid[id] == -1)
			return (kill_all_processes(params, id, 6));
		if (params->pid[id] == 0)
			if (create_process(philo, params, id))
				return (kill_all_processes(params, ++id, 7));
		usleep(50);
	}
	wait_exit_status(params, id);
	return (0);
}

// printf("%lld %d died\n",
