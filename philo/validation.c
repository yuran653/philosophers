/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 02:08:26 by jgoldste          #+#    #+#             */
/*   Updated: 2022/06/01 21:16:13 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	valid_args(t_params *params)
{
	if (params->num_of_philos > 200)
		return (1);
	if (params->time_to_die < 60)
		return (1);
	if (params->time_to_eat < 60)
		return (1);
	if (params->time_to_sleep < 60)
		return (1);
	return (0);
}

static int	ft_atoi_ph(char *str, int *num)
{
	unsigned long long int	number;

	number = 0;
	while (*str != '\0')
		number = number * 10 + *str++ - 48;
	if (number > 2147483647)
		return (-1);
	*num = number;
	return (*num);
}

static int	init_params(t_params *params, char *argv, int i)
{
	if (i == 1)
		if (ft_atoi_ph(argv, &params->num_of_philos) > 0)
			return (0);
	if (i == 2)
		if (ft_atoi_ph(argv, &params->time_to_die) > 0)
			return (0);
	if (i == 3)
		if (ft_atoi_ph(argv, &params->time_to_eat) > 0)
			return (0);
	if (i == 4)
		if (ft_atoi_ph(argv, &params->time_to_sleep) > 0)
			return (0);
	if (i == 5)
		if (ft_atoi_ph(argv, &params->times_must_eat) > 0)
			return (0);
	return (1);
}

static int	ft_isdigit(int str)
{
	return (str >= '0' && str <= '9');
}

t_params	*validation(t_params *params, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
			if (!ft_isdigit(argv[i][j]))
				return (free_return(params));
		if (init_params(params, argv[i], i))
			return (free_return(params));
	}
	if (i == 5)
		params->times_must_eat = 0;
	params->philo_exit = 0;
	params->philos_had_eaten = 0;
	params->start = get_timestamp();
	params->philo = NULL;
	params->forks = NULL;
	params->print = NULL;
	params->stop = NULL;
	params->meals_mut = NULL;
	params->thread = NULL;
	return (params);
}
