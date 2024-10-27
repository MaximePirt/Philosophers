/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <pierrot.maxime.pro@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 18:47:05 by mpierrot          #+#    #+#             */
/*   Updated: 2024/10/27 18:47:05 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleep_and_think(t_philo *philo)
{
	if (am_i_dead(philo))
		return (1);
	pthread_mutex_lock(&philo->up->lock);
	print_status(philo, "is sleeping");
	pthread_mutex_unlock(&philo->up->lock);
	ft_usleep(philo->up->tts);
	if (am_i_dead(philo))
		return (1);
	pthread_mutex_lock(&philo->up->lock);
	print_status(philo, "is thinking");
	pthread_mutex_unlock(&philo->up->lock);
	if (am_i_dead(philo))
		return (1);
	return (0);
}

int	eating_action(t_philo *philo)
{
	if (which_lock(philo) == 1)
		return (1);
	if (am_i_dead(philo))
	{
		which_unlock(philo);
		return (1);
	}
	pthread_mutex_lock(&philo->up->lock);
	philo->last_meal = get_current_time();
	print_status(philo, "is eating");
	philo->hm_eat++;
	pthread_mutex_unlock(&philo->up->lock);
	ft_usleep(philo->up->tte);
	which_unlock(philo);
	return (0);
}
