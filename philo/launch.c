/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 01:53:06 by jgoldste          #+#    #+#             */
/*   Updated: 2022/05/10 21:17:05 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	death_check(t_philo *philo, t_params *params)
// {
// 	if (params->philo_is_dead)
// 		return (1);
// 	if (get_timestamp() - philo->start > philo->death_time)
// 	{
// 		params->philo_is_dead = 1;
// 		params->dead_philo_id = philo->id;
// 		params->death_time = philo->death_time;
// 		return (1);
// 	}	
// 	return (0);
// }

void	print_status(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->print->mut);
	printf("[%7lldms] philosopher [%3d] %s\n",
		get_timestamp() - philo->start, philo->id, action);
	// printf("[%7lldms]->[%7lldms] philosopher [%3d] %s\n",
	// 	get_timestamp() - philo->start, philo->death_time, philo->id, action);
	// if (get_timestamp() - philo->start > philo->death_time)
	pthread_mutex_unlock(&philo->print->mut);
}

static int	philo_action(t_philo *philo, t_params *params)
{
	// if (death_check(philo, params))
	// 	return (1);
	// print_status(philo, "waiting for the right fork");
	pthread_mutex_lock(&philo->forks->fork[philo->right_fork]);
	print_status(philo, "has taken the right fork");
	// if (death_check(philo, params))
	// {
	// 	pthread_mutex_unlock(&philo->forks->fork[philo->right_fork]);
	// 	return (1);
	// }
	// print_status(philo, "waiting for the left fork");
	pthread_mutex_lock(&philo->forks->fork[philo->left_fork]);
	print_status(philo, "has taken the left fork");
	philo->last_meal = get_timestamp() - philo->start;
	philo->death_time = philo->last_meal + philo->time_to_die;
	philo->meals++;
	print_status(philo, "is eating");
	if (ft_sleep(philo->time_to_eat, params))
	{
		pthread_mutex_unlock(&philo->forks->fork[philo->right_fork]);
		pthread_mutex_unlock(&philo->forks->fork[philo->left_fork]);
		return (1);
	}
	pthread_mutex_unlock(&philo->forks->fork[philo->right_fork]);
	pthread_mutex_unlock(&philo->forks->fork[philo->left_fork]);
	print_status(philo, "is sleeping");
	if (ft_sleep(philo->time_to_sleep, params))
		return (1);
	// if (death_check(philo, params))
	// 	return (1);
	return (0);
}

void	*death_check(void *ptr)
{
	t_params	*params;
	t_philo		*philo;
	long long 	time;
	int			id;
	
	params = (t_params *)ptr;
	philo = params->philo;
	id = 0;
	while (id <= params->num_of_philos)
	{
		if (id == params->num_of_philos)
			id = 0;
		time = get_timestamp();
		if (philo[id].death_time < time - params->start)
		{
			params->philo_is_dead = 1;
			params->dead_philo_id = id;
			params->death_time = time - params->start;//philo[id].death_time;
			// printf("IS_DEAD = %d | ID = %d | TIME = %lldms > %lldms\n",
			// 	params->philo_is_dead, params->dead_philo_id, params->death_time, get_timestamp() - params->start);
			// print_status(&philo[id], "is died");
			return (NULL);
		}
		id++;
	}
	return (NULL);
}

static void	*philo_live(void *ptr)
{
	t_philo		*philo;
	t_params	*params;
	
	philo = (t_philo *)ptr;
	params = philo->params;
	if (philo->id % 2 == 0)
	{
		print_status(philo, "is thinking");
		usleep((philo->time_to_eat - 1) * 990);
	}
	while (1)//(params->philo_is_dead == 0 && philo->meals != philo->times_must_eat)
	{
		// if (death_check(philo, params))
		// 	return (NULL);
		if (params->philo_is_dead)
			return (NULL);
		if (philo->times_must_eat)
			if (philo->meals == philo->times_must_eat)
				return (NULL);
		if (philo_action(philo, params))
			return (NULL);
		print_status(philo, "is thinking");
	}
	return (NULL);
}

static int	create_threads(pthread_t *th, t_philo *philo, int num, int id)
{
	while(id < num)
	{
		if (pthread_create(&th[id], NULL, &philo_live, &philo[id]))
			return (7);
		id += 2;
	}
	return (0);
}

int	launch(t_params *params)
{
	t_philo		*philo;
	pthread_t	*th;
	pthread_t	death_t;
	int			num;
	int			id;

	philo = params->philo;
	th = params->thread;
	num = params->num_of_philos;
	if (create_threads(th, philo, num, 0) || create_threads(th, philo, num, 1))
		return (7);
	if (pthread_create(&death_t, NULL, &death_check, params))
		return (7);
	// if (pthread_join(death_t, NULL))
	// 	return (8);
	id = 0;
	while (id < params->num_of_philos)
		if (pthread_join(params->thread[id++], NULL))
			return (8);
	if (pthread_join(death_t, NULL))
		return (8);
	if (params->philo_is_dead)
		printf("[%7lldms] philosopher [%3d] is died\n",
			params->death_time, params->dead_philo_id);
	// if (params->philo_is_dead)
	// 	printf("[%7lldms] philosopher [%3d] is died\n",
	// 		params->death_time, params->dead_philo_id);
	return (0);
}

// int	launch(t_params *params)
// {
// 	t_philo	*philo;
// 	int		id;

// 	philo = params->philo;
// 	id = 0;
// 	while(id < params->num_of_philos)
// 	{
// 		if (pthread_create(&params->thread[id], NULL, &philo_live, &philo[id]))
// 			return (7);
// 		usleep(5);
// 		id += 2;
// 	}
// 	id = 1;
// 	while(id < params->num_of_philos)
// 	{
// 		if (pthread_create(&params->thread[id], NULL, &philo_live, &philo[id]))
// 			return (7);
// 		usleep(5);
// 		id += 2;
// 	}
// 	id = 0;
// 	while (id < params->num_of_philos)
// 		if (pthread_join(params->thread[id++], NULL))
// 			return (8);
// 	if (params->philo_is_dead)
// 		printf("[%7lldms] philosopher [%3d] is died\n",
// 			params->death_time, params->dead_philo_id);
// 	return (0);
// }
