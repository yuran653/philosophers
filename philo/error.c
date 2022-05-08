/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:23:46 by jgoldste          #+#    #+#             */
/*   Updated: 2022/05/08 05:25:43 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_error(int code)
{
	if (code == 4)
		write(2, "\e[1;31mERROR:\e[0m malloc allocation error\n", 43);
	else if (code == 5)
		write(2, "\e[1;31mERROR:\e[0m mutex initialization error\n", 46);
	else if (code == 6)
		write(2, "\e[1;31mERROR:\e[0m mutex destroy error\n", 39);
	else if (code == 7)
		write(2, "\e[1;31mERROR:\e[0m threads creating error\n", 42);
	else if (code == 8)
		write(2, "\e[1;31mERROR:\e[0m threads joining error\n", 41);
}

int	error_code_free_exit(int code, t_params *params)
{
	if (params->philo)
		free_null(params->philo);
	if (params->forks->fork)
		free_null(params->forks->fork);
	if (params->forks)
		free_null(params->forks);
	if (params->print)
		free_null(params->print);
	if (params->thread)
		free_null(params->thread);
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
