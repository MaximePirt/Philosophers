/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 23:23:19 by mpierrot          #+#    #+#             */
/*   Updated: 2024/05/25 06:13:12 by mpierrot         ###   ########.fr       */
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
	while (philo->up->hm_eat_to_end != philo->meal_progress
		&& !philo->up->terminate && !philo->up->is_dead)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&philo->right_fork);
		telling(philo, 0);
		philo->meal_progress++;
		telling(philo, 1);
		usleep(philo->up->tteat);
		philo->last_meal = get_current_time();
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		telling(philo, 2);
		usleep(philo->up->ttsleep);
		telling(philo, 3);
	}
	return (0);
}

void	*monitoring(void *args)
{
	t_data	*data;
	int		i;

	data = (t_data *)args;
	while (data->is_dead != 1 && !data->terminate)
	{
		i = 0;
		while (i < data->philo_nb)
		{
			pthread_mutex_lock(&data->print);
			if (check_time(data, i) != 0)
			{
				telling(data->phil[i], 4);
				break ;
			}
			if (data->phil[i]->meal_progress == data->hm_eat_to_end)
				data->terminate = 1;
			pthread_mutex_unlock(&data->print);
			i++;
		}
	}
	fprintf(stderr, "EOmonitoring %d\n", data->is_dead);
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
}
