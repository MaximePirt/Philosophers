/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:42:55 by mpierrot          #+#    #+#             */
/*   Updated: 2024/06/20 03:02:46 by mpierrot         ###   ########.fr       */
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
	if (philo->hm_eat == philo->up->hm_mte)
	{
		philo->up->eat_enough++;
		pthread_mutex_unlock(&philo->up->lock);
		return (1);
	}
	return (0);
}

void	*thread_phil(void *args)
{
	t_philo		*philo;
	long long	current_time;

	philo = (t_philo *)args;
	while (1)
	{
		if (am_i_dead(philo) == 1)
			break ;
		if (is_eating(philo) == 1)
			break ;
		if (am_i_dead(philo) == 1)
			break ;
		is_sleeping(philo);
		if (am_i_dead(philo) == 1)
			break ;
		pthread_mutex_lock(&philo->up->lock);
		current_time = get_current_time();
		printf("%lld %d is thinking\n",
			current_time - philo->up->starting_time, philo->id);
		pthread_mutex_unlock(&philo->up->lock);
	}
	return (NULL);
}
