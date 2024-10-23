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

int locking(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_lock(&philo->forks->left_fork) != 0)
			return (1);
		if (pthread_mutex_lock(philo->forks->right_fork) != 0)
		{
			pthread_mutex_unlock(&philo->forks->left_fork);
			return (1);
		}
	}
	else
	{
		if (pthread_mutex_lock(philo->forks->right_fork) != 0)
			return (1);
		if (pthread_mutex_lock(&philo->forks->left_fork) != 0)
		{
			pthread_mutex_unlock(philo->forks->right_fork);
			return (1);
		}
	}
	return (0);
}

int	which_lock(t_philo *philo)
{
	int i;

	i = locking(philo);
	if (i != 0)
		return (i);
//	if (am_i_dead(philo))
//	{
//		which_unlock(philo);
//		return (1);
//	}
	return (0);
}

void	which_unlock(t_philo *philo)
{
	if(philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->forks->right_fork);
		pthread_mutex_unlock(&philo->forks->left_fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->forks->left_fork);
		pthread_mutex_unlock(philo->forks->right_fork);
	}

}
