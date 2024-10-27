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
	pthread_mutex_destroy(&data->lock);
	free(data->phil);
}

//void	end_monitoring(t_data *data, pthread_t *threads)
//{
//	int	i;
//
//	i = 0;
//	(void) threads;
//	while (i < data->philo_nb)
//	{
////		pthread_join(threads[i], NULL);
//		i++;
//	}
//	free_all(data);
//}

int	monitoring_loop(t_data *data, int i)
{
	int	stop;

	stop = 0;
	while (stop == 0 && i < data->philo_nb)
	{
		pthread_mutex_lock(&data->lock);
		if (data->phil[i].last_meal + data->ttd < get_current_time())
		{
			print_status(&data->phil[i], "is dead");
			data->is_dead++;
			stop = 1;
		}
		if (data->phil[i].hm_eat == data->hm_mte)
			data->eat_enough++;
		if (data->eat_enough >= data->philo_nb)
		{
			data->terminate = 1;
			stop = 1;
		}
		pthread_mutex_unlock(&data->lock);
		i++;
		ft_usleep(50);
	}
	return (stop);
}

void	monitoring(t_data *data, pthread_t *threads)
{
	int	stop;
	int	i;

	stop = 0;
	(void) threads;
	while (stop == 0)
	{
		i = 0;
		stop = monitoring_loop(data, i);
	}
	pthread_mutex_lock(&data->lock);
	printf("All philo are dead [%d], "
		"eat enough  [%d]\n", data->is_dead, data->eat_enough);
	pthread_mutex_unlock(&data->lock);
//	end_monitoring(data, threads);
	free_all(data);
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
