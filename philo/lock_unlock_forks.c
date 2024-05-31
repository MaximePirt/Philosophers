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

void	which_lock(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->forks->left_fork);
		pthread_mutex_lock(philo->forks->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->forks->right_fork);
		pthread_mutex_lock(&philo->forks->left_fork);
	}
}

void	which_unlock(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->forks->left_fork);
		pthread_mutex_unlock(philo->forks->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->forks->right_fork);
		pthread_mutex_unlock(&philo->forks->left_fork);
	}
}
