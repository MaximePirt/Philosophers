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

//int test(t_philo *philo)
//{
//	if (philo->id == 0)
//	{
//		pthread_mutex_lock(philo->forks->right_fork);
//		if (am_i_dead(philo))
//		{
//			pthread_mutex_unlock(philo->forks->right_fork);
//			return (1);
//		}
//		pthread_mutex_lock(&philo->forks->left_fork);
//	}
//	else
//	{
//		pthread_mutex_lock(philo->forks->right_fork);
//		if (am_i_dead(philo))
//		{
//			pthread_mutex_unlock(philo->forks->right_fork);
//			return (1);
//		}
//		pthread_mutex_lock(&philo->forks->left_fork);
//	}
//	return (0);
//}

int	which_lock(t_philo *philo)
{
	if (am_i_dead(philo))
		return (1);
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
	if (am_i_dead(philo))
	{
		which_unlock(philo);
		return (1);
	}
	pthread_mutex_lock(&philo->up->lock);
	take_forks(philo);
	pthread_mutex_unlock(&philo->up->lock);
	return (0);
}

void	which_unlock(t_philo *philo)
{
	if (philo->id % 2 == 0)
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
void	take_forks(t_philo *philo)
{
	print_status(philo, "has taken a fork");
//	print_status(philo, "has taken a fork");
}