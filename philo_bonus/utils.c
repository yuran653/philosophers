/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 06:29:25 by jgoldste          #+#    #+#             */
/*   Updated: 2022/06/07 21:36:23 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_status(t_philo *philo, t_params *params, char *action)
{
	sem_wait(params->print);
	printf("\t[%7lldms] philosopher [%3d] %s\n",
		get_timestamp() - params->start, philo->id, action);
	sem_post(params->print);
}

long long	get_timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_sleep(long long m_secs)
{
	long long	stop;

	stop = get_timestamp() + m_secs;
	while (get_timestamp() < stop)
		usleep(250);
}

void	wait_exit_status(t_params *params, int id)
{
	int	status;

	while (waitpid(-1, &status, 0) > 0)
		if (WEXITSTATUS(status) == 1)
			kill_all_processes(params, id, 0);
}

int	kill_all_processes(t_params *params, int id, int value)
{
	while (--id >= 0)
	{
		if (params->pid[id])
		{
			kill(params->pid[id], SIGKILL);
			params->pid[id] = 0;
		}
	}
	return (value);
}

// printf("%lld %d %s\n",
