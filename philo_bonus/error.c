/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 06:29:32 by jgoldste          #+#    #+#             */
/*   Updated: 2022/06/03 06:41:29 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_null(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

t_params	*free_return(t_params *params)
{
	free(params);
	params = NULL;
	return (params);
}

static void	print_error(int code)
{
	if (code == 3)
		write(2, "\e[1;31mERROR:\e[0m arguments are not correct\n", 45);
	else if (code == 4)
		write(2, "\e[1;31mERROR:\e[0m malloc allocation error\n", 43);
	else if (code == 5)
		write(2, "\e[1;31mERROR:\e[0m semaphore open error\n", 40);
	else if (code == 6)
		write(2, "\e[1;31mERROR:\e[0m semaphore close error\n", 41);
	else if (code == 7)
		write(2, "\e[1;31mERROR:\e[0m process creating error\n", 42);
	// else if (code == 8)
	// 	write(2, "\e[1;31mERROR:\e[0m threads joining error\n", 41);
}

int	error_code_free_exit(int code, t_params *params)
{
	print_error(code);
	code = 0;
	if (sem_close_unlink(params->forks, FORKS))
		code  = 6;
	if (sem_close_unlink(params->print, PRINT))
		code  = 6;
	if (sem_close_unlink(params->stop, STOP))
		code  = 6;
	if (sem_close_unlink(params->meals_sem, MEALS_SEM))
		code  = 6;
	if (params->philo)
	{
		if (sem_close_unlink(params->philo->death_sem, DEATH_SEM))
			code  = 6;
		free_null(params->philo);
	}
	if (params->pid)
		free_null(params->pid);
	if (params)
		free_null(params);
	if (code == 0)
		return (0);
	print_error(code);
	return (1);
}

int	error_code(int code)
{
	if (code == 1)
		write(2, "\e[1;31mERROR:\e[0m wrong number of arguments\n", 45);
	else if (code == 2)
		write(2, "\e[1;31mERROR:\e[0m malloc allocation error\n", 43);
	else if (code == 3)
		write(2, "\e[1;31mERROR:\e[0m arguments are not correct\n", 45);
	return (1);
}
