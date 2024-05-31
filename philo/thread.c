/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:42:55 by mpierrot          #+#    #+#             */
/*   Updated: 2024/05/31 04:00:08 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	am_i_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->up->lock);
	if (philo->up->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->up->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->up->lock);
	return (0);
}

int	have_i_eat_enough(t_philo *philo)
{
	pthread_mutex_lock(&philo->up->lock);
	if (philo->up->hm_mte == philo->hm_eat)
	{
		pthread_mutex_unlock(&philo->up->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->up->lock);
	return (0);
}

int	take_forks(t_philo *philo)
{
	long long	current_time;

	pthread_mutex_lock(&philo->up->lock);
	current_time = get_current_time();
	printf("%lld %d has taken a fork\n",
		current_time - philo->up->starting_time, philo->id);
	pthread_mutex_unlock(&philo->up->lock);
	if (am_i_dead(philo) == 1 || have_i_eat_enough(philo) == 1)
	{
		which_unlock(philo);
		return (1);
	}
	pthread_mutex_lock(&philo->up->lock);
	current_time = get_current_time();
	printf("%lld %d has taken a fork\n",
		current_time - philo->up->starting_time, philo->id);
	pthread_mutex_unlock(&philo->up->lock);
	if (am_i_dead(philo) == 1 || have_i_eat_enough(philo) == 1)
	{
		which_unlock(philo);
		return (1);
	}
	return (0);
}

int	sleep_and_think(t_philo *philo)
{
	long long	current_time;

	pthread_mutex_lock(&philo->up->lock);
	current_time = get_current_time();
	printf("%lld %d is sleeping\n",
		current_time - philo->up->starting_time, philo->id);
	pthread_mutex_unlock(&philo->up->lock);
	usleep(philo->up->tts * 1000);
	if (am_i_dead(philo) == 1 || have_i_eat_enough(philo) == 1)
		return (1);
	pthread_mutex_lock(&philo->up->lock);
	current_time = get_current_time();
	printf("%lld %d is thinking\n",
		current_time - philo->up->starting_time, philo->id);
	pthread_mutex_unlock(&philo->up->lock);
	return (0);
}

void	*thread_phil(void *args)
{
	t_philo		*philo;
	long long	current_time;

	philo = (t_philo *)args;
	while (1)
	{
		if (am_i_dead(philo) == 1 || have_i_eat_enough(philo) == 1)
			break ;
		which_lock(philo);
		if (take_forks(philo) == 1)
			break ;
		pthread_mutex_lock(&philo->up->lock);
		current_time = get_current_time();
		philo->last_meal = current_time;
		printf("%lld %d is eating\n",
			philo->last_meal - philo->up->starting_time, philo->id);
		philo->hm_eat++;
		pthread_mutex_unlock(&philo->up->lock);
		usleep(philo->up->tte * 1000);
		which_unlock(philo);
		if (am_i_dead(philo) == 1 || have_i_eat_enough(philo) == 1
			|| sleep_and_think(philo) == 1)
			break ;
	}
	return (NULL);
}
