/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 03:38:02 by mpierrot          #+#    #+#             */
/*   Updated: 2024/05/31 04:00:56 by mpierrot         ###   ########.fr       */
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

typedef struct s_fork
{
	int				used;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
}					t_fork;

typedef struct s_philo
{
	long long	last_meal;
	int			hm_eat;
	int			id;
	t_data		*up;
	t_fork		*forks;

}				t_philo;

typedef struct s_data
{
	long long		starting_time;
	int				philo_nb;
	int				ttd;
	int				tte;
	int				tts;
	int				hm_mte;
	t_philo			*phil;
	pthread_mutex_t	lock;
	int				is_dead;
	int 			eat_enough;

}					t_data;

// Parsing
int			parsing_args(t_data *data, int argc, char **arg);

// init
void		*fill_my_philo_args(t_data *data, long *args);
int			init_memory(pthread_t **threads, t_data *data);
void		init_threads(t_data *data);

//lock and unlock
int			which_lock(t_philo *philo);
void		which_unlock(t_philo *philo);

// Threads functions
void		monitoring(t_data *data, pthread_t *threads);
void		*thread_phil(void *args);
int			am_i_dead(t_philo *philo);
int			have_i_eat_enough(t_philo *philo);
void		print_status(t_philo *philo, char *status);

// lib
long		ft_atol(const char *str);
size_t		ft_strlen(const char *str);
int			ft_check_only_string(char *res, char *c);
void		ft_putstr_fd(char *s, int fd);
long long	get_current_time(void);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
//int			ft_usleep(long long milliseconds);
char		*ft_itoa(int n);
void		ft_putnbr(int n);


#endif