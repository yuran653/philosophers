/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 06:29:32 by jgoldste          #+#    #+#             */
/*   Updated: 2022/06/07 14:15:44 by jgoldste         ###   ########.fr       */
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
		write(2, "\e[1;31mERROR:\e[0m process creating error\n", 42);
	else if (code == 7)
		write(2, "\e[1;31mERROR:\e[0m thread creating/detach error\n", 41);
}

int	error_code_free_exit(int code, t_params *params)
{
	print_error(code);
	kill_all_processes(params, params->num_of_philos, 0);
	sem_post(params->print);
	sem_close_unlink(params->forks, FORKS);
	sem_close_unlink(params->print, PRINT);
	sem_close_unlink(params->philos_had_eaten, PHILOS_HAD_EATEN);
	if (params->philo)
		free_null(params->philo);
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
