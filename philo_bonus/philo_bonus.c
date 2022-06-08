/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 06:29:05 by jgoldste          #+#    #+#             */
/*   Updated: 2022/06/08 15:56:21 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	if (valid_args(params))
		return (error_code_free_exit(3, params));
	if (init_philo(params))
		return (error_code_free_exit(4, params));
	// if (calloc_arrays(params->philo, params))
	// 	return (error_code_free_exit(4, params));
	if (calloc_pid(params))
		return (error_code_free_exit(4, params));
	// if (init_sem(params->philo, params))
	// 	return (error_code_free_exit(5, params));
	if (init_sem(params))
		return (error_code_free_exit(5, params));
	err = launch(params->philo, params);
	return (error_code_free_exit(err, params));
}
