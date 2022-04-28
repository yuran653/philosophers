/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:56:57 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/27 21:18:05 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_code(int code)
{
	if (code == 1)
		write(2, "\e[1;31mERROR:\e[0m wrong number of arguments\n", 45);
	if (code == 2)
		write(2, "\e[1;31mERROR:\e[0m malloc allocation error\n", 43);
	if (code == 3)
		write(2, "\e[1;31mERROR:\e[0m arguments are not correct\n", 45);
	return (1);
}

int	main(int argc, char **argv)
{
	t_params	*params;

	if (argc < 5 || argc > 6)
		return (error_code(1));
	params = (t_params *)malloc(sizeof(t_params));
	if (!params)
		return (error_code(2));
	params = validation(params, argv);
	if (!params)
		return (error_code(3));
	printf("num_of_philo = %d\ntime_to_die = %d\ntime_to_eat = %d\ntime_to_sleep = %d\ntimes_must_eat = %d\n",
		params->num_of_philo, params->time_to_die, params->time_to_eat, params->time_to_sleep, params->times_must_eat);
	free(params);
	return (0);
}
