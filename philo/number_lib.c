/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_lib.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <pierrot.maxime.pro@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 18:44:58 by mpierrot          #+#    #+#             */
/*   Updated: 2024/10/27 18:44:58 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putnbr(int n)
{
	int	nb;

	nb = n;
	if (nb < 0)
	{
		nb = nb * -1;
		write(1, "-", 1);
	}
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	if (nb >= 0 && nb <= 9)
		ft_putchar_fd(nb + '0', 1);
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
