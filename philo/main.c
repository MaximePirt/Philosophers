/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 23:23:19 by mpierrot          #+#    #+#             */
/*   Updated: 2024/05/25 12:31:37 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*threading(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	pthread_mutex_lock(&philo->up->print);
	printf("Me voila et voila mon id %d:\n", philo->id);
	pthread_mutex_unlock(&philo->up->print);
	while (1)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&philo->right_fork);
		pthread_mutex_lock(&philo->up->dead_lock);
		if (philo->up->is_dead == 1 || philo->up->terminate == 1)
		{
			fprintf(stderr, "on s arrete ici\n");
			pthread_mutex_unlock(&philo->up->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->up->dead_lock);
		telling(philo, 0);
		philo->meal_progress++;
		telling(philo, 1);
		philo->last_meal = get_current_time();
		usleep(philo->up->tteat);
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		telling(philo, 2);
		pthread_mutex_lock(&philo->up->dead_lock);
		usleep(philo->up->ttsleep);
		pthread_mutex_unlock(&philo->up->dead_lock);
		telling(philo, 3);
	}
	return (0);
}

void	*monitoring(void *args)
{
	t_data	*data;
	int		i;

	data = (t_data *)args;
	while (1)
	{
		i = 0;
		while (i < data->philo_nb)
		{
			pthread_mutex_lock(&data->dead_lock);
			if (check_time(data, i) == 1)
			{
				telling(data->phil[i], 4);
				usleep(200);
				pthread_mutex_lock(&data->print);
				fprintf(stderr, "i QUIT2m\n");
				pthread_mutex_unlock(&data->print);
				pthread_mutex_unlock(&data->dead_lock);
				break ;
			}
			if (need_to_quit(data->phil[i]) == 1)
			{
				usleep(200);
				pthread_mutex_lock(&data->print);
				fprintf(stderr, "i QUIT\n");
				pthread_mutex_unlock(&data->print);
				pthread_mutex_unlock(&data->dead_lock);
				break ;
			}
			usleep(200);
			pthread_mutex_unlock(&data->dead_lock);
			i++;
		}
	}
	pthread_mutex_lock(&data->print);
	fprintf(stderr, "EOmonitoring %d\n", data->is_dead);
	usleep(1000);
	pthread_mutex_unlock(&data->print);
	end_all(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("wrong input", 2);
		return (1);
	}
	data = parsing_args(argc, argv);
	if (data.is_args_ok == -1)
	{
		ft_putstr_fd("wrong input", 2);
		return (1);
	}
	initiate_monitoring(&data);
	fprintf(stderr, "FINI\n");
}
