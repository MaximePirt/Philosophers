/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   am_i_dead.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 04:30:05 by mpierrot          #+#    #+#             */
/*   Updated: 2024/05/25 06:06:53 by mpierrot         ###   ########.fr       */
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
	pthread_mutex_lock(&data->dead_lock);
	fprintf(stderr, "vla ttdie %zu\n", data->ttdie);
	fprintf(stderr, "vla lastmeal %zu\n", data->phil[i]->last_meal);
	fprintf(stderr, "vla starttime %zu\n", data->starting_time);
	fprintf(stderr, "vla currentime %zu\n", current_time - data->starting_time);
	fprintf(stderr, "vla comparaisonm %zu\n", (data->phil[i]->last_meal
			+ data->ttdie) - data->starting_time);
	if ((data->phil[i]->last_meal + data->ttdie) - data->starting_time)
	{
		fprintf(stderr, "too much time %d is dead bro %zu\n", data->phil[i]->id,
			current_time - data->starting_time);
		data->is_dead = 1;
		return (1);
	}
	pthread_mutex_unlock(&data->dead_lock);
	return (0);
}

void	end_all(t_data *data)
{
	int	i;

	i = 0;
	while (data->phil[i])
	{
		pthread_join(data->phil[i]->philo_thread, NULL);
		i++;
	}
	pthread_join(data->monitor, NULL);
	fprintf(stderr, "all clean\n");
}
