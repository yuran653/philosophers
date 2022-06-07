/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 06:29:19 by jgoldste          #+#    #+#             */
/*   Updated: 2022/06/07 14:12:22 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

sem_t	*ft_sem_open(char *name, int oflag, mode_t mode, int value)
{
	sem_t	*sem;

	sem_unlink(name);
	sem = sem_open(name, oflag, mode, value);
	return (sem);
}

int	init_sem(t_params *params)
{
	params->forks = ft_sem_open(FORKS, O_CREAT, 0644, params->num_of_philos);
	if (params->forks == SEM_FAILED)
		return (1);
	params->print = ft_sem_open(PRINT, O_CREAT, 0644, 1);
	if (params->print == SEM_FAILED)
		return (1);
	params->philos_had_eaten
		= ft_sem_open(PHILOS_HAD_EATEN, O_CREAT, 0644, 1);
	if (params->philos_had_eaten == SEM_FAILED)
		return (1);
	return (0);
}

void	sem_close_unlink(sem_t *sem, char *name)
{
	if (sem)
	{
		sem_unlink(name);
		sem_close(sem);
		sem = NULL;
	}
}

int	calloc_pid(t_params *params)
{
	int	id;

	id = 0;
	params->pid = (pid_t *)malloc(sizeof(pid_t) * params->num_of_philos);
	if (!params->pid)
		return (1);
	while (id < params->num_of_philos)
		params->pid[id++] = 0;
	return (0);
}

int	init_philo(t_params *params)
{
	params->philo = (t_philo *)malloc(sizeof(t_philo));
	if (!params->philo)
		return (1);
	params->philo->id = 0;
	params->philo->meals = 0;
	params->philo->death_time = params->time_to_die;
	params->philo->last_meal = params->start;
	return (0);
}
