/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mpierrot          #+#    #+#             */
/*   Updated: 2024/10/20 18:02:38 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_usleep(size_t milliseconds, t_data *data)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
	{
		pthread_mutex_lock(&data->lock);
		if (data->is_dead == 1)
		{
			pthread_mutex_unlock(&data->lock);
			break ;
		}
		pthread_mutex_unlock(&data->lock);
		usleep(700);
	}
	return (0);
}

int	is_eating(t_philo *philo)
{
	long long	current_time;

	pthread_mutex_lock(&philo->up->lock);
	current_time = get_current_time();
	philo->last_meal = current_time;
	printf("%lld %d is eating\n",
		philo->last_meal - philo->up->starting_time, philo->id);
	philo->hm_eat++;
	if (have_i_eat_enough(philo) == 1)
		return (1);
	pthread_mutex_unlock(&philo->up->lock);
	ft_usleep(philo->up->tte, philo->up);
	return (0);
}

void	is_sleeping(t_philo *philo)
{
	long long	current_time;

	pthread_mutex_lock(&philo->up->lock);
	current_time = get_current_time();
	printf("%lld %d is sleeping\n",
		current_time - philo->up->starting_time, philo->id);
	pthread_mutex_unlock(&philo->up->lock);
	ft_usleep(philo->up->tts, philo->up);
}
