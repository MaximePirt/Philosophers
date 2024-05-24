/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 23:23:19 by mpierrot          #+#    #+#             */
/*   Updated: 2024/05/24 00:52:40 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*function(void *arg)
{
	t_philo	*philo;

	(void)arg;
	philo = (t_philo *)arg;
	printf("Me voila et voila mon id %d:\n", philo->id);
	while (philo->up->hm_eat_to_end != philo->meal_progress
		&& !(philo->up->terminate))
	{
		fprintf(stderr, "Am i dead? [%d]", philo->up->is_dead);
		if (philo->up->is_dead == 1)
			break ;
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&philo->right_fork);
		philo->meal_progress++;
		philo->last_meal = get_current_time();
		fprintf(stderr, "%d Currently eating\n", philo->id);
		usleep(philo->up->tteat * 1000);
		fprintf(stderr, "%d Currently sleeping\n", philo->id);
		usleep(philo->up->ttsleep * 1000);
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_lock(&philo->up->print);
		fprintf(stderr, "%d Currently thinking\n", philo->id);
		pthread_mutex_unlock(&philo->up->print);
		// unlock
	}
	fprintf(stderr, "out %d\n", philo->id);
	return ((void *)arg);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	*monitoring(void *args)
{
	t_data	*data;
	int		current_time;
	int		i;
	int		j;

	data = (t_data *)args;
	j = 0;
	while (j != 1)
	{
		i = 0;
		while (j != 1 && i < data->philo_nb)
		{
			current_time = get_current_time();
			fprintf(stderr, "ttdie : [%zu] and the minus : [%d]\n\n",
				data->ttdie, current_time);
			if (current_time - data->phil[i]->last_meal >= data->ttdie)
				j = -1;
			i++;
		}
	}
	// end the func
	fprintf(stderr, "end\n");
	j = 0;
	while (j < data->philo_nb)
	{
		data->phil[j]->up->is_dead = 1;
		fprintf(stderr, "joining thread num %d\n", j);
		if (pthread_join(data->phil[j]->philo_thread, NULL) != 0)
		{
			ft_putstr_fd("A problem occur with thread joining", 2);
			return (NULL);
		}
		fprintf(stderr, "AHAHAHAHHAHAHAHAH\n");
		fprintf(stderr, "%d Is dead\n", data->phil[j]->id);
		j++;
	}
	return (NULL);
}

int	go_threading(t_data *data)
{
	int	i;

	// pthread_t	th[data.philo_nb];
	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_create(&data->phil[i]->philo_thread, NULL, &function,
				(void *)data->phil[i]) != 0)
		{
			ft_putstr_fd("A problem occur with thread creation", 2);
			return (-1);
		}
		i++;
	}
	pthread_create(&data->monitor, NULL, &monitoring, data);
	ft_usleep(10);
	return (0);
}

// void	philo_fork(t_data data)
// {
// 	int		i;
// 	t_data	tmp;

// 	tmp = data;
// 	i = 0;
// 	while (i < data.philo_nb - 1)
// 	{
// 		tmp.phil[i]->right_fork = *tmp.phil[i + 1]->left_fork;
// 		i++;
// 	}
// }
void	philo_fork(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		if (i == data->philo_nb - 1)
		{
			// Last philosopher's right fork points to the first philosopher's left fork
			data->phil[i]->right_fork = *data->phil[0]->left_fork;
		}
		else
		{
			// Each philosopher's right fork is the next philosopher's left fork
			data->phil[i]->right_fork = *data->phil[i + 1]->left_fork;
		}
		i++;
	}
}
// global->philo[i].right_fork = (i + 1) % global->nb_philo;

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

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
	i = 0;
	while (i < data.philo_nb)
	{
		if (pthread_mutex_init(&data.forks[i], NULL) != 0)
			return (-1);
		i++;
	}
	printf("ouhouh\n");
	philo_fork(&data);
	go_threading(&data);
	printf("eheh\n");
	while (i < data.philo_nb)
	{
		pthread_mutex_destroy(&data.forks[i]);
		i++;
	}
	return (0);
}
