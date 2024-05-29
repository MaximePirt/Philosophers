/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:04:04 by mpierrot          #+#    #+#             */
/*   Updated: 2024/05/29 03:31:01 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *fill_my_philo_args(t_data *data, long *args)
{
	data->starting_time = get_current_time();
	data->philo_nb = args[1];
	data->ttd = args[2];
	data->tte = args[3];
	data->tts = args[4];
	data->hm_mte = args[5];
	data->is_dead = 0;
	init_threads(data);
	return (NULL);
}

void init_forks(t_data *data)
{
	int i;
	t_fork *tmp;

	tmp = data->forks;
	tmp->used = 0;
	tmp->left_fork = tmp + 1;
	tmp->right_fork = tmp + data->philo_nb - 1;
	i = 1;
	while (i < data->philo_nb)
	{
		tmp->used = 0;
		if (i == data->philo_nb - 1)
			tmp->left_fork = tmp - (data->philo_nb - 1);
		else
			tmp->left_fork = tmp + 1;
		tmp->right_fork = tmp - 1;
		tmp++;
		i++;
	}
}

void init_threads(t_data *data)
{
	int i;
	pthread_t *threads;

	if (!init_memory(&threads, data))
		return;
	i = 0;
	pthread_mutex_init(&data->lock, NULL);
	while (i < data->philo_nb)
	{
		data->phil[i].id = i;
		data->phil[i].hm_eat = 0;
		data->phil[i].up = data;
		data->phil[i].last_meal = get_current_time();
		pthread_create(&threads[i], NULL, &thread_phil, &data->phil[i]);
		i++;
	}
	init_forks(data);
	monitoring(data, threads);
	free(threads);
}

int init_memory(pthread_t **threads, t_data *data)
{
	*threads = malloc(sizeof(pthread_t) * data->philo_nb);
	if (!*threads)
		return (0);
	data->phil = malloc(sizeof(t_philo) * data->philo_nb);
	if (!data->phil)
	{
		free(threads);
		return (0);
	}
	data->forks = malloc(sizeof(t_fork) * data->philo_nb);
	if (!data->forks)
	{
		free(threads);
		free(data->phil);
		return (0);
	}
	return (1);
}
