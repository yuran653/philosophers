/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:49:27 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/25 20:03:42 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>

// A normal C function that is executed as a thread
// when its name is specified in pthread_create()
void *myThreadFun(void *thread_id)
{
	sleep(1);
	printf("Printing GeeksQuiz from Thread \n");
	return NULL;
}

int main()
{
	pthread_t thread_id;
	printf("Before Thread\n");
	pthread_create(&thread_id, NULL, myThreadFun, &thread_id);
	pthread_join(thread_id, NULL);
	printf("After Thread\n");
	exit(0);
}


// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h> //Header file for sleep(). man 3 sleep for details.
// #include <pthread.h>

// // A normal C function that is executed as a thread
// // when its name is specified in pthread_create()
// void *myThreadFun(void *vargp)
// {
// 	sleep(1);
// 	printf("Printing GeeksQuiz from Thread \n");
// 	return NULL;
// }

// int main()
// {
// 	pthread_t thread_id;
// 	printf("Before Thread\n");
// 	pthread_create(&thread_id, NULL, myThreadFun, NULL);
// 	pthread_join(thread_id, NULL);
// 	printf("After Thread\n");
// 	exit(0);
// }
