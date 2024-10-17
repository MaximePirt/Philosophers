#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_mutex_t	print_mutex;

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, strlen(str));
}

void	ft_usleep(int ms)
{
	usleep(ms * 1000);
}

typedef struct s_phil
{
	pthread_t	philo_thread;
	int			id;
	int			*should_terminate;
}				t_phil;

void	*function(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
	while (!*(phil->should_terminate))
	{
		pthread_mutex_lock(&print_mutex);
		printf("Thread %d en cours de travail.\n", phil->id);
		pthread_mutex_unlock(&print_mutex);
		sleep(1); // Simule un travail continu
	}
	pthread_mutex_lock(&print_mutex);
	printf("Thread %d terminé.\n", phil->id);
	pthread_mutex_unlock(&print_mutex);
	return (NULL);
}

int	main(void)
{
	int		philo_nb;
	t_phil	**phil;
	int		should_terminate;

	philo_nb = 5;
	phil = malloc(sizeof(t_phil *) * philo_nb);
	should_terminate = 0;
	if (phil == NULL)
	{
		ft_putstr_fd("A problem occurred with memory allocation for phil array\n",
			2);
		return (-1);
	}
	if (pthread_mutex_init(&print_mutex, NULL) != 0)
	{
		ft_putstr_fd("A problem occurred with mutex initialization\n", 2);
		return (-1);
	}
	for (int i = 0; i < philo_nb; i++)
	{
		phil[i] = (t_phil *)malloc(sizeof(t_phil));
		if (phil[i] == NULL)
		{
			ft_putstr_fd("A problem occurred with memory allocation\n", 2);
			return (-1);
		}
		phil[i]->id = i;
		phil[i]->should_terminate = &should_terminate;
	}
	for (int i = 0; i < philo_nb; i++)
	{
		pthread_mutex_lock(&print_mutex);
		printf("Création du thread %d\n", i);
		pthread_mutex_unlock(&print_mutex);
		if (pthread_create(&phil[i]->philo_thread, NULL, &function,
				(void *)phil[i]) != 0)
		{
			ft_putstr_fd("A problem occurred with thread creation\n", 2);
			return (-1);
		}
		pthread_mutex_lock(&print_mutex);
		printf("Thread %d créé.\n", i);
		pthread_mutex_unlock(&print_mutex);
	}
	ft_usleep(10);
	// Simule un travail principal pendant 5 secondes
	sleep(5);
	should_terminate = 1;
	for (int i = 0; i < philo_nb; i++)
	{
		pthread_mutex_lock(&print_mutex);
		printf("En attente du thread %d\n", i);
		pthread_mutex_unlock(&print_mutex);
		if (pthread_join(phil[i]->philo_thread, NULL) != 0)
		{
			ft_putstr_fd("A problem occurred with thread joining\n", 2);
			return (-1);
		}
		pthread_mutex_lock(&print_mutex);
		printf("Thread %d rejoint.\n", i);
		pthread_mutex_unlock(&print_mutex);
	}
	for (int i = 0; i < philo_nb; i++)
	{
		free(phil[i]);
	}
	free(phil);
	pthread_mutex_destroy(&print_mutex);
	printf("Tous les threads ont terminé.\n");
	return (0);
}
