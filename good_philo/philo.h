/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:59:31 by mpierrot          #+#    #+#             */
/*   Updated: 2024/05/29 03:22:03 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_data t_data;

typedef struct s_fork
{
	int used;
	void *left_fork;
	void *right_fork;
} t_fork;

typedef struct s_philo
{
	long long last_meal;
	int hm_eat;
	int id;
	t_data *up;

} t_philo;

typedef struct s_data
{
	long long starting_time;
	int philo_nb;
	int ttd;
	int tte;
	int tts;
	int hm_mte;
	t_philo *phil;
	t_fork *forks;
	pthread_mutex_t lock;
	int is_dead;

} t_data;

// Parsing
int parsing_args(t_data *data, int argc, char **arg);

// init
void *fill_my_philo_args(t_data *data, long *args);
int init_memory(pthread_t **threads, t_data *data);
void init_threads(t_data *data);

// Threads functions
void monitoring(t_data *data, pthread_t *threads);
void *thread_phil(void *args);
int am_i_dead(t_philo *philo);

// lib
long ft_atol(const char *str);
size_t ft_strlen(const char *str);
int ft_check_only_string(char *res, char *c);
void ft_putstr_fd(char *s, int fd);
long long get_current_time(void);

#endif