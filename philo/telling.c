/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   telling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 04:21:15 by mpierrot          #+#    #+#             */
/*   Updated: 2024/05/25 11:22:20 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	telling(t_philo *philo, int sentence)
{
	size_t	current_time;

	current_time = get_current_time();
	pthread_mutex_lock(&philo->up->print);
	if (sentence == 0)
		fprintf(stderr, "%ld %d has taken a fork\n ", current_time
			- philo->up->starting_time, philo->id);
	else if (sentence == 1)
		fprintf(stderr, "%ld %d is eating\n ", current_time
			- philo->up->starting_time, philo->id);
	else if (sentence == 2)
		fprintf(stderr, "%ld %d is sleeping\n ", current_time
			- philo->up->starting_time, philo->id);
	else if (sentence == 3)
		fprintf(stderr, "%ld %d is thinking\n ", current_time
			- philo->up->starting_time, philo->id);
	else if (sentence == 4)
		fprintf(stderr, "%ld %d died\n ", current_time
			- philo->up->starting_time, philo->id);
	pthread_mutex_unlock(&philo->up->print);
}
