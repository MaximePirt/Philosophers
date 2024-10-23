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

static int	ft_usleep(long long milliseconds)
{
	long long	start;

	start = get_current_time();
	while (get_current_time() - start < milliseconds)
		usleep(100);
	return (0);
}

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
//	while (i < data->philo_nb)
//	{
//		pthread_join(threads[i], NULL);
//		i++;
//	}
//	free_all(data);
//}

//void	monitoring(t_data *data, pthread_t *threads)
//{
//	int stop;
//
//	stop = 0;
//	while(1)
//	{
//		pthread_mutex_lock(&data->lock);
//		if (data->eat_enough == data->philo_nb || data->is_dead)
//			stop = 1;
//		pthread_mutex_unlock(&data->lock);
//		if (stop)
//			break ;
//		usleep(100);
//	}
//	pthread_mutex_lock(&data->lock);
//	printf("All philo are dead [%d], eat enough  [%d]\n",data->is_dead,  data->eat_enough);
//	pthread_mutex_unlock(&data->lock);
//	end_monitoring(data, threads);
//}

void	checking_philo_health(t_data *data)
{
	long long	time;
	int			i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_lock(&data->lock);
		time = get_current_time();
		if (time - data->phil[i].last_meal > data->ttd)
		{
			data->is_dead = 1;
			printf("%lld %d is dead\n",
				   get_current_time() - data->starting_time, data->phil[i].id);
			pthread_mutex_unlock(&data->lock);
			break ;
		}
		pthread_mutex_unlock(&data->lock);
		i++;
	}
}

void	monitoring(t_data *data, pthread_t *threads)
{
	int			i;

	while (1)
	{
		ft_usleep(100);
		checking_philo_health(data);
		pthread_mutex_lock(&data->lock);
		if (data->is_dead == 1 || data->eat_enough >= data->philo_nb)
		{
			pthread_mutex_unlock(&data->lock);
			break ;
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
