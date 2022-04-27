/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 20:41:55 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/25 21:02:42 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int	x;

void	*print_str1()
{
	x++;
	printf("1. VALUE OF X = %d IN PID [%5d]\n", (int)x, getpid());
	return (NULL);
}

void	*print_str2()
{
	printf("2. VALUE OF X = %d IN PID [%5d]\n", (int)x, getpid());
	return (NULL);
}

int	main()
{
	pthread_t	t1, t2;

	x = 0;
	if (pthread_create(&t1, NULL, &print_str1, NULL))
		exit(EXIT_FAILURE);
	if (pthread_create(&t2, NULL, &print_str2, NULL))
		exit(EXIT_FAILURE);
	if (pthread_join(t1, NULL))
		exit(EXIT_FAILURE);
	if (pthread_join(t2, NULL))
		exit(EXIT_FAILURE);
	return (0);
}