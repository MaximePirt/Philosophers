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

void	print_status(t_philo *philo, char *status)
{
	long long	time;

	if (ft_strncmp(status, "has taken a fork", 1) == 0)
	{
		time = get_current_time() - philo->up->starting_time;
		printf("%lld %d %s\n%lld %d %s\n",
			time, philo->id, status, time, philo->id, status);
	}
	else
		printf("%lld %d %s\n",
			get_current_time() - philo->up->starting_time, philo->id, status);
}

int	am_i_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->up->lock);
	if (philo->up->is_dead)
	{
		pthread_mutex_unlock(&philo->up->lock);
		return (1);
	}
	if (philo->up->terminate == 1)
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
	if (philo->hm_eat == philo->up->hm_mte)
		philo->up->eat_enough++;
	if (philo->up->eat_enough == philo->up->philo_nb)
	{
		pthread_mutex_unlock(&philo->up->lock);
		return (1);
	}
	if (philo->up->terminate == 1)
	{
		pthread_mutex_unlock(&philo->up->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->up->lock);
	return (0);
}

void	*thread_phil(void *args)
{
	t_philo		*philo;

	philo = (t_philo *)args;
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (1)
	{
		if (am_i_dead(philo) == 1)
			break ;
		if (eating_action(philo) == 1)
			break ;
		if (am_i_dead(philo) == 1)
			break ;
		if (have_i_eat_enough(philo) == 1)
			break ;
		if (am_i_dead(philo) == 1)
			break ;
		if (sleep_and_think(philo) == 1)
			break ;
	}
	return (NULL);
}
