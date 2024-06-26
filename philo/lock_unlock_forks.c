/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_unlock_forks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 03:59:28 by mpierrot          #+#    #+#             */
/*   Updated: 2024/05/31 03:59:44 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int test(t_philo *philo)
{
	if (philo->id == 0)
	{
		if (philo->up->phil[philo->up->philo_nb - 1].forks->used == 1)
			return (1);
		pthread_mutex_lock(philo->forks->right_fork);
		pthread_mutex_lock(&philo->forks->left_fork);
	}
	else
	{
		if (philo->up->phil[philo->id - 1].forks->used == 1)
			return (1);
		pthread_mutex_lock(philo->forks->right_fork);
		pthread_mutex_lock(&philo->forks->left_fork);
	}
	philo->forks->used = 1;
	return (0);
}

int	which_lock(t_philo *philo)
{
	if (am_i_dead(philo))
		return (1);
	pthread_mutex_lock(&philo->up->lock);
	if (test(philo) == 1)
	{
		pthread_mutex_unlock(&philo->up->lock);
		return (2);
	}
//	take_forks(philo);
	print_status(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->up->lock);
	if (am_i_dead(philo))
	{
		which_unlock(philo);
		return (1);
	}
	return (0);
}

void	which_unlock(t_philo *philo)
{
	philo->forks->used = 0;
	pthread_mutex_unlock(&philo->forks->left_fork);
	pthread_mutex_unlock(philo->forks->right_fork);
}
void	take_forks(t_philo *philo)
{
	print_status(philo, "has taken a fork");
//	print_status(philo, "has taken a fork");
}