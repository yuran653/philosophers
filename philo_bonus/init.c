/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 06:29:19 by jgoldste          #+#    #+#             */
/*   Updated: 2022/06/03 06:42:41 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static sem_t	*ft_sem_open(char *name, int oflag, mode_t mode, int value)
{
	sem_t	*sem;

	sem = sem_open(name, oflag, mode, value);
	if (sem == SEM_FAILED)
	{
		if (sem_unlink(name) == 0)
			sem = sem_open(name, oflag, mode, value);
		else
			return (SEM_FAILED);
	}
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
	params->stop = ft_sem_open(STOP, O_CREAT, 0644, 1);
	if (params->stop == SEM_FAILED)
		return (1);
	params->meals_sem = ft_sem_open(MEALS_SEM, O_CREAT, 0644, 1);
	if (params->meals_sem == SEM_FAILED)
		return (1);
	params->philo->death_sem = ft_sem_open(DEATH_SEM, O_CREAT, 0644, 1);
	if (params->philo->death_sem == SEM_FAILED)
		return (1);
	return (0);
}

int	sem_close_unlink(sem_t *sem, char *name)
{
	if (sem)
	{
		if (sem_close(sem) == -1)
			return (1);
		else if (sem_unlink(name) == -1)
			return (1);
		sem = NULL;
	}
	return (0);
}

int	malloc_pid(t_params *params)
{
	params->pid = (pid_t *)malloc(sizeof(pid_t) * params->num_of_philos);
	if (!params->pid)
		return (1);
	return (0);
}

int	init_philo(t_params *params)
{
	params->philo = (t_philo *)malloc(sizeof(t_philo));
	if (!params->philo)
		return (1);
	params->philo->id = 0;
	params->philo->meals = 0;
	params->philo->death_time = params->start + params->time_to_die;
	params->philo->last_meal = params->start;
	params->philo->death_sem = NULL;
	return (0);
}
