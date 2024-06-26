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

void print_status(t_philo *philo, char *status)
{
	long long	time;

	if(ft_strncmp(status, "has taken a fork", 1) == 0)
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
	long long	time;

	pthread_mutex_lock(&philo->up->lock);
	time = get_current_time();
	if (philo->up->eat_enough == philo->up->philo_nb || philo->up->is_dead)
	{
		pthread_mutex_unlock(&philo->up->lock);
		return (1);
	}
	if (time - philo->last_meal >= philo->up->ttd)
	{
		printf("current_tine [%lld] starting time [%lld] \nTime to death [%d]  last meal [%lld] minus [%lld]\n",
			   get_current_time(), philo->up->starting_time, philo->up->ttd, philo->last_meal, time - philo->last_meal);
		printf("%lld %d %s\n",
			get_current_time() - philo->last_meal, philo->id, "he died at that time");
		printf("%lld %d %s\n",
			time - philo->up->starting_time, philo->id, "is dead");
		philo->up->is_dead = 1;
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
	pthread_mutex_unlock(&philo->up->lock);
	return (0);
}



int	sleep_and_think(t_philo *philo)
{
	if(am_i_dead(philo))
		return (1);
	pthread_mutex_lock(&philo->up->lock);
	print_status(philo, "is sleeping");
	pthread_mutex_unlock(&philo->up->lock);
	usleep(philo->up->tts * 1000);
	if(am_i_dead(philo))
		return (1);
	pthread_mutex_lock(&philo->up->lock);
	print_status(philo, "is thinking");
	pthread_mutex_unlock(&philo->up->lock);
	return (0);
}

int eating_action(t_philo *philo)
{
	int i;

	i = which_lock(philo);
	if(i != 0)
		return (i);
	pthread_mutex_lock(&philo->up->lock);
	philo->last_meal = get_current_time();
	print_status(philo, "is eating");
	philo->hm_eat++;
	pthread_mutex_unlock(&philo->up->lock);
	usleep(philo->up->tte * 1000);
	which_unlock(philo);
	return (0);
}

void	*thread_phil(void *args)
{
	t_philo		*philo;
	int i;

	philo = (t_philo *)args;

	if(philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		i = eating_action(philo);
		if (i == 1)
			break;
		else if (i == 2)
			continue;
		if (have_i_eat_enough(philo) == 1)
			break;
		if (sleep_and_think(philo) == 1)
			break;
	}
	return (NULL);
}

/*
 * Dead
 * Take fork
 * Dead
 * eat
 * Dead
 * sleep
 * Dead
 * think
 */
