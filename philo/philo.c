/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:56:57 by jgoldste          #+#    #+#             */
/*   Updated: 2022/05/07 06:00:40 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (malloc_arrays(params))
		return (error_code_free_exit(4, params));
	if (mutex_init(params))
		return (error_code_free_exit(5, params));
	params->start = get_timestamp();
	philos_init(params);
	err = launch(params);
	if (params->philo_is_dead)
		printf("[%7lldms] philosopher [%3d] died (printed before mutex destroy)\n",
			params->death_time, params->dead_philo_id);
	if (mutex_destroy(params))
		return (error_code_free_exit(6, params));
	if (params->philo_is_dead)
		printf("[%7lldms] philosopher [%3d] died\n",
			params->death_time, params->dead_philo_id);
	return (error_code_free_exit(err, params));
}
