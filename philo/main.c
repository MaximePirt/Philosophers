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

int	monitoring_check(t_data *data, int i)
{
	pthread_mutex_lock(&data->lock);
	if (get_current_time() - data->phil[i].last_meal > data->ttd)
	{
		data->is_dead = 1;
		if (data->phil[i].hm_eat != data->hm_mte)
			printf("%lld %d is dead\n",
				(get_current_time() - data->starting_time), data->is_dead);
		pthread_mutex_unlock(&data->lock);
		return (1);
	}
	pthread_mutex_unlock(&data->lock);
	return (0);
}

void	monitoring(t_data *data, pthread_t *threads)
{
	int	i;

	while (1)
	{
		usleep(100);
		i = 0;
		while (i < data->philo_nb)
		{
			if (monitoring_check(data, i) == 1)
				break ;
			i++;
		}
		if (am_i_dead(&data->phil[1]) == 1
			|| have_i_eat_enough(&data->phil[1]) == 1)
			break ;
	}
	end_monitoring(data, threads);
	return ;
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
