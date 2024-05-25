/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 23:22:57 by mpierrot          #+#    #+#             */
/*   Updated: 2024/05/25 06:04:11 by mpierrot         ###   ########.fr       */
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

typedef struct s_data	t_data;

typedef enum e_bool
{
	true = 1,
	false = 0,
	none = -1
}						t_bool;

typedef struct s_philo
{
	int					id;
	int					meal_progress;
	size_t				last_meal;
	pthread_t			philo_thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		right_fork;
	t_data				*up;

}						t_philo;

typedef struct s_data
{
	int					philo_nb;
	size_t				ttdie;
	int					tteat;
	int					ttsleep;
	int					hm_eat_to_end;
	int					is_args_ok;
	int					terminate;
	size_t				starting_time;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		print;
	pthread_t			monitor;
	t_bool				is_dead;
	t_philo				**phil;
	pthread_mutex_t		*forks;
}						t_data;

// parsing func
t_data					parsing_args(int argc, char **args);

// Init
t_data					fill_my_philo_args(long *j);
void					initiate_monitoring(t_data *data);
void					end_thread(t_data *data);

// announce
void					telling(t_philo *philo, int sentence);

// Monitoring and threads
void					*threading(void *args);
void					*monitoring(void *args);

// lib func recode
void					ft_putstr_fd(char *s, int fd);
int						ft_check_only_string(char *res, char *c);
size_t					ft_strlen(const char *str);
long					ft_atol(const char *str);

// am i dead
size_t					get_current_time(void);
int						check_time(t_data *data, int i);

// end
void					end_all(t_data *data);

#endif