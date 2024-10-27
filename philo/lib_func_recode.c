/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_func_recode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 23:40:00 by mpierrot          #+#    #+#             */
/*   Updated: 2024/05/31 03:51:33 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	long	i;
	long	j;
	long	z;

	i = 0;
	j = 1;
	z = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 45)
		j *= -1;
	if (str[i] == 45 || str[i] == 43)
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		z = z * 10 + (str[i] - '0');
		i++;
	}
	z *= j;
	return (z);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_check_only_string(char *res, char *c)
{
	int		i;
	int		j;
	size_t	check;

	check = 0;
	j = 0;
	i = 0;
	while (res[i])
	{
		while (c[j])
		{
			if (res[i] == c[j])
				check++;
			j++;
		}
		if (check == 0)
			return (-1);
		check = 0;
		j = 0;
		i++;
	}
	return (1);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (!s || !fd)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	ft_usleep(useconds_t time)
{
	long long	start;

	start = get_current_time();
	while ((get_current_time() - start) < time)
		usleep(time / 10);
	return (0);
}

long long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		ft_putstr_fd("gettimeofday error\n", 2);
	return ((time.tv_sec) * 1000 + (time.tv_usec) / 1000);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}