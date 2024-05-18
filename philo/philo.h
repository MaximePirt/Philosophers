/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 23:22:57 by mpierrot          #+#    #+#             */
/*   Updated: 2024/05/18 21:44:26 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int	philo_nb;
	int	ttdie;
	int	tteat;
	int	ttsleep;
	int	notemeat;
	int	is_args_ok;

}		t_philo;

// parsing func
t_philo	parsing_args(int argc, char **args);

// lib func recode
void	ft_putstr_fd(char *s, int fd);
int		ft_check_only_string(char *res, char *c);
size_t	ft_strlen(const char *str);
long	ft_atol(const char *str);

#endif