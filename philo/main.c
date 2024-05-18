/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 23:23:19 by mpierrot          #+#    #+#             */
/*   Updated: 2024/05/18 02:44:32 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// pthread_mutex_lock(&mutex);
// pthread_mutex_uncd lock(&mutex);

// pthread_create(&mutex, NULL, &function, NULL);

// pthread_join(mutex, NULL);
// the first NULL part is what return we want to get from the thread in function
// for example : int *res : pthread_join(mutex, (void **)&res);


int	main(int argc, char **argv)
{
	pthread_mutex_t mutex;
	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("wrong input", 2);
		return (1);
	}
	pthread_init(&mutex, NULL);
	pthread_destroy(&mutex);
	(void)argv;
	return (0);
}
