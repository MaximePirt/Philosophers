/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:50:41 by mpierrot          #+#    #+#             */
/*   Updated: 2024/05/31 03:57:55 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_destroy(&data->phil[i].forks->left_fork);
		free(data->phil[i].forks);
		i++;
	}
	free(data->phil);
}

void	end_monitoring(t_data *data, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free_all(data);
}

void	monitoring(t_data *data, pthread_t *threads)
{
	int	stop;
	int eat_enough;

	while (1)
	{
		pthread_mutex_lock(&data->lock);
		stop = data->is_dead;
		eat_enough = data->is_terminated;
		pthread_mutex_unlock(&data->lock);
		if (stop == 1 || eat_enough == data->philo_nb)
			break ;
	}
	printf("All philo are dead [%d], is terminate  [%d]\n",stop,  data->is_terminated);
	end_monitoring(data, threads);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if ((argc < 5 || argc > 6) || !parsing_args(&data, argc, argv))
	{
		ft_putstr_fd("Error \n", 2);
		return (1);
	}
	printf("starting_time: %lld\n", data.starting_time);
	printf("philo_nb: %d\n", data.philo_nb);
	printf("ttd: %d\n", data.ttd);
	printf("tte: %d\n", data.tte);
	printf("tts: %d\n", data.tts);
	printf("hm_mte: %d\n", data.hm_mte);
	return (0);
}
