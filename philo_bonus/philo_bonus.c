/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 06:29:05 by jgoldste          #+#    #+#             */
/*   Updated: 2022/06/02 05:13:53 by jgoldste         ###   ########.fr       */
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
	if (malloc_pid(params))
		return (error_code_free_exit(4, params));
	if (init_philo(params))
		return (error_code_free_exit(4, params));
	if (init_sem(params))
		return (error_code_free_exit(5, params));
	err = launch(params->philo, params);
	// err = 0;
	printf("\t---OK---\n");
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
