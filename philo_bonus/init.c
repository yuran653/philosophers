/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 06:29:19 by jgoldste          #+#    #+#             */
/*   Updated: 2022/06/01 06:29:20 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_philo(t_params *params)
{
	t_philo	*philo;
	
	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (1);
	philo->id = 0;
	philo->meals = 0;
	philo->death_time = params->start + params->time_to_die;
	philo->last_meal = params->start;
	philo->death_sem = 0;
	params->philo = philo;
	return (0);
}
