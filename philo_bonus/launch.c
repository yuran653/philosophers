/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 01:53:06 by jgoldste          #+#    #+#             */
/*   Updated: 2022/06/05 19:36:49 by jgoldste         ###   ########.fr       */
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
		// printf("%lld %d died\n",
			time - params->start, philo->id);
		exit (1);
	}
}

// static void	*check_philos_had_eaten(void *ptr)
// {
// 	t_params	*params;
// 	// int			i;

// 	// i = 0;
// 	params = (t_params *)ptr;
// 	ft_sleep(params->time_to_eat * 2 + params->time_to_sleep);
// 	// while (i < params->num_of_philos)
// 		sem_wait(params->philos_had_eaten);
// 	// exit (1);
// }

static void	*death_meals_check(void *ptr)
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

static void	wait_exit_status(t_params *params, int id)
{
	int	status;
	
	while (waitpid(-1, &status, 0) > 0)
		if (WEXITSTATUS(status) == 1)
			kill_all_processes(params, id, 0);
}

int	launch(t_philo *philo, t_params *params)
{
	pthread_t	stop_t;
	// pthread_t	meals_t;
	int			id;
	
	stop_t = NULL;
	id = 0;
	while (id < params->num_of_philos)
	{
		params->pid[id] = fork();
		if (params->pid[id] == -1)
			return (kill_all_processes(params, id, 7));
		if (params->pid[id] == 0)
		{
			philo->id = id + 1;
			if (params->times_must_eat)
			{
				sem_wait(params->philos_had_eaten);
				// if (pthread_create(&meals_t, NULL, &check_philos_had_eaten, params))
				// 	return (kill_all_processes(params, id, 8));
				// if (pthread_detach(meals_t))
				// 	return (kill_all_processes(params, id, 9));
			}
			if (pthread_create(&stop_t, NULL, &death_meals_check, params))
				return (kill_all_processes(params, id, 8));
			if (pthread_detach(stop_t))
				return (kill_all_processes(params, id, 9));
			philo_live(philo, params);
		}
		usleep(50);
		id++;
	}
	wait_exit_status(params, id);
	return (0);
}

// printf("%lld %d died\n",
