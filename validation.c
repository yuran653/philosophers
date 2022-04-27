/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 02:08:26 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/27 03:39:07 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi_ph(char *str)
{
	unsigned long long int	number;
	int						sign;

	sign = 1;
	number = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == 43 || *str == 45)
	{
		if (*str == 45)
			sign = -1;
		str++;
	}
	while (*str != '\0' && *str >= 48 && *str <= 57)
	{
		number = number * 10 + *str - 48;
		str++;
	}
	if (sign == 1 && number >= 9223372036854775807u)
		return (-1);
	if (sign == -1 && number >= 9223372036854775807u)
		return (0);
	return (sign * number);
}

int	ft_isdigit(int str)
{
	return (str >= '0' && str <= '9');
}

int	init_params(t_params *params, char *argv, int i)
{
	if (i == 1)
		params->num_of_philo = ft_atoi_ph(argv);
	if (!params->num_of_philo)
		return (1);
	if (i == 2)
		params->time_to_die = ft_atoi_ph(argv);
	if (!params->time_to_die)
		return (1);
	if (i == 3)
		params->time_to_eat = ft_atoi_ph(argv);
	if (!params->time_to_eat)
		return (1);
	if (i == 4)
		params->time_to_sleep = ft_atoi_ph(argv);
	if (!params->time_to_sleep)
		return (1);
	if (i == 5)
		params->times_must_eat = ft_atoi_ph(argv);
	if (!params->times_must_eat)
		return (1);
	return (0);
}

t_params	*validation(char **argv)
{
	t_params	*params;
	int			i;
	int			j;
	
	i = 0;
	params = (t_params *)malloc(sizeof(t_params));
	if (!params)
		return (NULL);
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
			if (!ft_isdigit(argv[i][j]))
				return (NULL);
		if (init_params(params, argv[i], i))
			return (NULL);
	}
	if (i == 5)
		params->times_must_eat = 0;
	return (params);
}