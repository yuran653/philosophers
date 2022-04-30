/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:56:57 by jgoldste          #+#    #+#             */
/*   Updated: 2022/05/01 02:44:32 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_null(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

int	error_code_free_exit(int code, t_params *params)
{
	
	if (params->philo)
		free_null(params->philo);
	if (params->thread)
		free_null(params->thread);
	if (params)
		free_null(params);
	if (code == 0)
		return (0);
	else if (code == 4)
		write(2, "\e[1;31mERROR:\e[0m malloc allocation error\n", 43);
	else if (code == 5)
		write(2, "\e[1;31mERROR:\e[0m threads creating error\n", 42);
	else if (code == 6)
		write(2, "\e[1;31mERROR:\e[0m threads joining error\n", 41);
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

int	main(int argc, char **argv)
{
	t_params	*params;
	int			err;

	if (argc < 5 || argc > 6)
		return (error_code(1));
	params = (t_params *)malloc(sizeof(t_params));
	if (!params)
		return (error_code(2));
	params = validation(params, argv);
	if (!params)
		return (error_code(3));
	params->philo = (t_philo *)malloc(sizeof(t_philo) * params->num_of_philo);
	if (!params->philo)
		return (error_code_free_exit(4, params));
	params->thread = (pthread_t *)malloc(sizeof(pthread_t) * params->num_of_philo);
	if (!params->thread)
		return (error_code_free_exit(4, params));
	err = launch(params);
	return (error_code_free_exit(err, params));
}

// printf("num_of_philo = %d\ntime_to_die = %d\ntime_to_eat = %d\ntime_to_sleep = %d\ntimes_must_eat = %d\n",
	// 	params->num_of_philo, params->time_to_die, params->time_to_eat, params->time_to_sleep, params->times_must_eat);
