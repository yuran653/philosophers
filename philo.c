/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:56:57 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/27 03:40:20 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_params	*params;
	
	if (argc < 5 || argc > 6)
		return (1);
	params = validation(argv);
	if (!params)
		return (1);
	printf("num_of_philo = %d\ntime_to_die = %d\ntime_to_eat = %d\ntime_to_sleep = %d\ntimes_must_eat = %d\n",
		params->num_of_philo, params->time_to_die, params->time_to_eat, params->time_to_sleep, params->times_must_eat);
	free(params);
	return (0);
}