/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 21:09:50 by jgoldste          #+#    #+#             */
/*   Updated: 2022/06/09 21:17:03 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_null(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}

void	free_null_array(void **array, int size)
{
	int	i;

	i = -1;
	if (array)
		while (++i < size)
			free(array[i]);
	free(array);
	array = NULL;
}

t_params	*free_return(t_params *params)
{
	if (params)
		free(params);
	params = NULL;
	return (params);
}
