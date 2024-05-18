/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 23:22:57 by mpierrot          #+#    #+#             */
/*   Updated: 2024/05/18 02:03:19 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>


// parsing func
int parsing_args(char **args);


// lib func recode
void	ft_putstr_fd(char *s, int fd);

#endif