/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 02:04:53 by mpierrot          #+#    #+#             */
/*   Updated: 2024/05/25 13:53:29 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	fill_my_philo_args(long *j)
{
	t_data	data;
	int		i;

	i = 0;
	data.starting_time = get_current_time();
	data.philo_nb = j[1];
	data.ttdie = j[2];
	data.tteat = j[3];
	data.ttsleep = j[4];
	data.hm_eat_to_end = j[5];
	data.terminate = 0;
	data.is_dead = 0;
	data.phil = malloc(sizeof(t_philo *) * data.philo_nb);
	data.forks = malloc(sizeof(pthread_mutex_t) * data.philo_nb);
	pthread_mutex_init(&data.dead_lock, NULL);
	pthread_mutex_init(&data.print, NULL);
	while (i < data.philo_nb)
	{
		data.phil[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!data.phil[i])
		{
			data.is_args_ok = -1;
			return (data);
		}
		data.phil[i]->id = i + 1;
		data.phil[i]->left_fork = &data.forks[i];
		data.phil[i]->up = &data;
		data.phil[i]->meal_progress = 0;
		data.phil[i]->last_meal = get_current_time();
		i++;
	}
	data.phil[i] = NULL;
	return (data);
}

void	initiate_monitoring(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_create(&data->phil[i]->philo_thread, NULL, &threading,
			(void *)data->phil[i]);
		usleep(200);
		i++;
	}
	usleep(20);
	pthread_create(&data->monitor, NULL, &monitoring, (void *)data);
	usleep(20);
	pthread_join(data->monitor, NULL);
	return ;
}

void	end_thread(t_data *data)
{
	(void)data;
	return ;
}