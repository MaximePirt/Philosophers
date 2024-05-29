/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:50:41 by mpierrot          #+#    #+#             */
/*   Updated: 2024/05/29 04:23:38 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void free_all(t_data *data)
{
	free(data->forks);
	free(data->phil);
}

void monitoring(t_data *data, pthread_t *threads)
{
	int i;
	// monitoring philo
	while (1)
	{
		usleep(100);
		i = 0;
		while (i < data->philo_nb)
		{
			pthread_mutex_lock(&data->lock);
			long long time = get_current_time();
			// printf("soustraction : [%lld], ttd [%d]\n", (time - data->phil[i].last_meal), data->ttd);
			if (time - data->phil[i].last_meal > data->ttd)
			{
				data->is_dead = 1;
				printf("%d\n", data->is_dead);
				pthread_mutex_unlock(&data->lock);
				break;
			}
			pthread_mutex_unlock(&data->lock);
			i++;
		}
		pthread_mutex_lock(&data->lock);
		if (data->is_dead == 1)
		{
			printf("EHHH MORT\n");
			pthread_mutex_unlock(&data->lock);
			break;
		}
		pthread_mutex_unlock(&data->lock);
	}

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free_all(data);
	return;
}

int main(int argc, char **argv)
{
	t_data data;
	(void)argc;
	(void)argv;

	if (!parsing_args(&data, argc, argv))
		return (1);

	printf("starting_time: %lld\n", data.starting_time);
	printf("philo_nb: %d\n", data.philo_nb);
	printf("ttd: %d\n", data.ttd);
	printf("tte: %d\n", data.tte);
	printf("tts: %d\n", data.tts);
	printf("hm_mte: %d\n", data.hm_mte);
	return (0);
}
