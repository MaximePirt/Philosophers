/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 23:23:19 by mpierrot          #+#    #+#             */
/*   Updated: 2024/05/18 22:32:06 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// pthread_mutex_lock(&mutex);
// pthread_mutex_uncd lock(&mutex);

// if (pthread_create(&mutex, NULL, &function, NULL) != 0)
// {
// 	perror("failed to create thread");
// }
// Last NULL is arg which will be sent into function

// if (pthread_join(mutex, NULL) != 0)
//  	perror("failed to join thread");
// the first NULL part is what return we want to get from the thread in function
// for example : int *res : pthread_join(mutex, (void **)&res);

int	main(int argc, char **argv)
{
	t_philo	philo;

	// pthread_mutex_t	mutex;
	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("wrong input", 2);
		return (1);
	}
	philo = parsing_args(argc, argv);
	if (philo.is_args_ok == -1)
	{
		ft_putstr_fd("wrong input", 2);
		return (1);
	}
	fprintf(stderr, "Here %d", philo.ttdie);
	// pthread_init(&mutex, NULL);
	// pthread_destroy(&mutex);
	return (0);
}
