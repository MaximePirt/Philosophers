/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   telling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 04:21:15 by mpierrot          #+#    #+#             */
/*   Updated: 2024/05/25 06:01:21 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	telling(t_philo *philo, int sentence)
{
	char	**tab;
	size_t	current_time;

	pthread_mutex_lock(&philo->up->print);
	current_time = get_current_time();
	tab = malloc(sizeof(char **) * 5);
	tab[0] = "has taken a fork";
	tab[1] = "is eating";
	tab[2] = "is sleeping";
	tab[3] = "is thinking";
	tab[4] = "died";
	fprintf(stderr, "%ld %d %s\n", current_time - philo->up->starting_time,
		philo->id, tab[sentence]);
	free(tab);
	pthread_mutex_unlock(&philo->up->print);
}
