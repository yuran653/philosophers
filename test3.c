/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 21:01:30 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/26 17:55:28 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void *threadFunc(void *arg)
{
    char *s = (char *) arg;
    printf("%s", s);
    return (void *) strlen(s);
}

int main(int argc, char *argv[])
{
    pthread_t t1;
    void *res;
    int s;

    s = pthread_create(&t1, NULL, threadFunc, "Hello world\n");
    if (s != 0)
        exit(EXIT_FAILURE);
    printf("Message from main()\n");
    s = pthread_join(t1, &res);
    if (s != 0)
        exit(EXIT_FAILURE);
     printf("Thread returned %ld\n", (long) res);
	return (0);
}
