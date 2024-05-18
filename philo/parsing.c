/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 23:22:48 by mpierrot          #+#    #+#             */
/*   Updated: 2024/05/18 21:58:06 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*copy(char *tmp, size_t a, size_t i)
{
	while (tmp[i])
	{
		tmp[a] = tmp[i];
		a++;
		i++;
	}
	tmp[a] = '\0';
	return (tmp);
}

static char	*noptozero(char *tmp)
{
	size_t	i;
	size_t	a;
	size_t	len;

	len = ft_strlen(tmp);
	i = 0;
	a = 0;
	if ((tmp[0] == 43 || tmp[0] == 45) && tmp[1] && tmp[1] != ' ')
	{
		a++;
		i++;
	}
	while (tmp[i] == '0')
		i++;
	if (!tmp[i])
	{
		tmp[0] = '0';
		tmp[1] = '\0';
		return (tmp);
	}
	tmp = copy(tmp, a, i);
	return (tmp);
}

static int	ft_check_numbers(char **args)
{
	size_t	i;

	i = 1;
	while (args[i])
	{
		if (ft_check_only_string(args[i], "0123456789") == -1)
			return (-1);
		i++;
	}
	return (1);
}

static t_philo	fill_my_philo_args(long *j)
{
	t_philo	philo;

	philo.philo_nb = j[1];
	philo.ttdie = j[2];
	philo.tteat = j[3];
	philo.ttsleep = j[4];
	philo.notemeat = j[5];
	return (philo);
}

t_philo	parsing_args(int argc, char **arg)
{
	int		i;
	long	j[6];
	size_t	len;
	t_philo	philo;

	philo.is_args_ok = 0;
	if (ft_check_numbers(arg) == -1)
		philo.is_args_ok = -1;
	i = 0;
	while (arg[i] && philo.is_args_ok == 0)
	{
		arg[i] = noptozero(arg[i]);
		len = ft_strlen(arg[i]);
		j[i] = ft_atol(arg[i]);
		if ((len > 11 || !len) && (j[i] > 2147483647 || j[i] < -2147483648))
			return (philo);
		if ((len > 11 || !len) || (j[i] > 2147483647 || j[i] < -2147483648))
			return (philo);
		i++;
	}
	if (philo.is_args_ok == -1)
		return (philo);
	if (argc == 5)
		j[5] = 2147483646;
	return (fill_my_philo_args(j));
}
