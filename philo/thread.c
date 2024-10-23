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

void print_status(t_philo *philo, char *status)
{
	long long	time;

	time = get_current_time() - philo->up->starting_time;
	if (ft_strncmp(status, "has taken a fork", 1) == 0)
		printf("%lld %d %s\n", time, philo->id, status);
	printf("%lld %d %s\n", time, philo->id, status);
}



//int	am_i_dead(t_philo *philo)
//{
//	long long	time;
//
//	pthread_mutex_lock(&philo->up->lock);
//	time = get_current_time();
//	if (philo->up->eat_enough == philo->up->philo_nb || philo->up->is_dead)
//	{
//		pthread_mutex_unlock(&philo->up->lock);
//		return (1);
//	}
//	if (time - philo->last_meal >= philo->up->ttd)
//	{
//		printf("%lld %d %s\n",
//			time - philo->up->starting_time, philo->id, "is dead");
//		philo->up->is_dead = 1;
//		pthread_mutex_unlock(&philo->up->lock);
//		return (1);
//	}
//	pthread_mutex_unlock(&philo->up->lock);
//	return (0);
//}

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

//int	have_i_eat_enough(t_philo *philo)
//{
//	pthread_mutex_lock(&philo->up->lock);
//	if (philo->hm_eat == philo->up->hm_mte)
//		philo->up->eat_enough++;
//	pthread_mutex_unlock(&philo->up->lock);
//	if (philo->up->eat_enough == philo->up->philo_nb)
//		return (1);
//	return (0);
//}

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



int	sleep_and_think(t_philo *philo)
{
	if (am_i_dead(philo))
		return (1);
	pthread_mutex_lock(&philo->up->lock);
	print_status(philo, "is sleeping");
	pthread_mutex_unlock(&philo->up->lock);
	ft_usleep(philo->up->tts, philo->up);
	if (am_i_dead(philo))
		return (1);
	pthread_mutex_lock(&philo->up->lock);
	print_status(philo, "is thinking");
	pthread_mutex_unlock(&philo->up->lock);
	return (0);
}

int is_eating(t_philo *philo)
{
	int i;

	i = which_lock(philo);
	if (i != 0)
		return (i);
	pthread_mutex_lock(&philo->up->lock);
	philo->last_meal = get_current_time();
	print_status(philo, "is eating");
	philo->hm_eat++;
	pthread_mutex_unlock(&philo->up->lock);
	ft_usleep(philo->up->tte, philo->up);
	which_unlock(philo);

	return (0);
}


//void	*thread_phil(void *args)
//{
//	t_philo		*philo;
//	int i;
//
//	philo = (t_philo *)args;
//
//	if(philo->id % 2 == 0)
//		usleep(100);
//	while (1)
//	{
//		i = eating_action(philo);
//		if (i == 1)
//			break;
//		else if (i == 2)
//			continue;
//		if (have_i_eat_enough(philo) == 1)
//			break;
//		if (sleep_and_think(philo) == 1)
//			break;
//	}
//	return (NULL);
//}

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
