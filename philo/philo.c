/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:56:57 by jgoldste          #+#    #+#             */
/*   Updated: 2022/05/30 19:06:56 by jgoldste         ###   ########.fr       */
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
	if (valid_args(params))
		return (error_code_free_exit(3, params));
	if (malloc_arrays(params, params->num_of_philos))
		return (error_code_free_exit(4, params));
	if (mutex_init(params))
		return (error_code_free_exit(5, params));
	philos_init(params);
	err = launch(params);
	if (mutex_destroy(params))
		return (error_code_free_exit(6, params));
	return (error_code_free_exit(err, params));
}

// static void	check_meals_amount(t_params *params)
// {
// 	int	wrong_amount = 0;

// 	for (int id = 0; id < params->num_of_philos; id++)
// 		if (params->philo[id].meals < params->times_must_eat)
// 			wrong_amount++;
// 	if (wrong_amount)
// 	{
// 		printf("KO: [%d] philosopher(s) had eaten less than [%d] times\n",
// 			wrong_amount, params->times_must_eat);
// 	}
// 	else
// 	{
// 		printf("OK: All of philosophers had eaten at least [%d] times\n",
// 			params->times_must_eat);
// 	}
// }

// static void print_meals_amount(t_params *params)
// {
// 	for (int id = 0; id < params->num_of_philos; id++)
// 	{
// 		if (params->philo[id].meals < params->times_must_eat)
// 		{
// 			printf("Philosofer [%3d] hadn't eaten enough: ",
// 				params->philo[id].id);
// 			printf("[%d] times instead of [%d] times\n",
// 				params->philo[id].meals, params->times_must_eat);
// 		}
// 		else
// 			printf("Philosofer [%3d] had eaten [%d] times\n",
// 				params->philo[id].id,  params->philo[id].meals);
// 	}
// }
