/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   am_i_dead.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 04:30:05 by mpierrot          #+#    #+#             */
/*   Updated: 2024/05/25 13:53:24 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		ft_putstr_fd("gettimeofday error\n", 2);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
int	check_time(t_data *data, int i)
{
	size_t	current_time;

	current_time = get_current_time();
	if ((current_time - data->phil[i]->last_meal) > data->ttdie)
	{
		pthread_mutex_lock(&data->dead_lock);
		fprintf(stderr, "too much time %d is dead bro %zu\n", data->phil[i]->id,
			current_time - data->starting_time);
		data->is_dead = 1;
		pthread_mutex_unlock(&data->dead_lock);
		return (1);
	}
	return (0);
}

void	end_all(t_data *data)
{
	int	i;

	ft_putstr_fd("je suis la !\n", 2);
	i = 0;
	usleep(300);
	while (data->phil[i])
	{
		pthread_join(data->phil[i]->philo_thread, NULL);
		i++;
	}
	// pthread_join(data->monitor, NULL);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->print);
	fprintf(stderr, "all clean\n");
}

int	need_to_quit(t_philo *philo)
{
	pthread_mutex_lock(&philo->up->dead_lock);
	check_time(philo->up, philo->id);
	pthread_mutex_unlock(&philo->up->dead_lock);
	if (philo->up->is_dead == 1 || philo->up->terminate == 1
		|| philo->up->hm_eat_to_end == philo->meal_progress)
		return (1);
	return (0);
}
