/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:56:57 by jgoldste          #+#    #+#             */
/*   Updated: 2022/05/04 05:47:42 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_null(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

long long	get_timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	ft_sleep(long long m_secs, t_params *params)
{
	long long	start;

	start = get_timestamp();
	while(!params->philo_is_dead)
	{
		if (get_timestamp() - start >= m_secs)
			return (0);
	}
	return(0);
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->params->print);
	printf("[%7lldms] philosopher[%03d] %s\n",
		get_timestamp() - philo->start, philo->id, status);
		// get_timestamp() - philo->params->start, philo->id, status);
	pthread_mutex_unlock(&philo->params->print);
}

int	error_code_free_exit(int code, t_params *params)
{
	
	if (params->philo)
		free_null(params->philo);
	if (params->forks)
		free_null(params->forks);
	if (params)
		free_null(params);
	if (code == 0)
		return (0);
	else if (code == 4)
		write(2, "\e[1;31mERROR:\e[0m malloc allocation error\n", 43);
	else if (code == 5)
		write(2, "\e[1;31mERROR:\e[0m mutex initialization error\n", 46);
	else if (code == 6)
		write(2, "\e[1;31mERROR:\e[0m mutex destroy error\n", 39);
	else if (code == 7)
		write(2, "\e[1;31mERROR:\e[0m threads creating error\n", 42);
	else if (code == 8)
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
	params->philo = (t_philo *)malloc(sizeof(t_philo) * params->num_of_philos);
	if (!params->philo)
		return (error_code_free_exit(4, params));
	params->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * params->num_of_philos);
	if (!params->forks)
		return (error_code_free_exit(4, params));
	philos_init(params);
	if (mutex_init(params))
		return (error_code_free_exit(5, params));
	err = launch(params);
	// printf("PHILOS HAVE EATEN -%d- TIMES\n", params->philos_have_eaten);
	if (mutex_destroy(params))
		return (error_code_free_exit(6, params));
	return (error_code_free_exit(err, params));
}
