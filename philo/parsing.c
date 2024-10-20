/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 23:22:48 by mpierrot          #+#    #+#             */
/*   Updated: 2024/05/29 06:49:57 by mpierrot         ###   ########.fr       */
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

int	check_args_validity(char **arg, long *j)
{
	size_t	len;
	int		i;

	i = 0;
	while (arg[i])
	{
		arg[i] = noptozero(arg[i]);
		len = ft_strlen(arg[i]);
		j[i] = ft_atol(arg[i]);
		if (len > 11 || !len || j[i] > 2147483647 || j[i] < -2147483648)
			return (1);
		i++;
	}
	return (0);
}

int	parsing_args(t_data *data, int argc, char **arg)
{
	long	j[6];

	if (argc < 5 || argc > 6)
	{
		write(1, "Error: invalid argument\n", 25);
		return (1);
	}
	if (ft_check_numbers(arg) == -1 || check_args_validity(arg, j))
	{
		write(2, "Error: invalid argument\n", 25);
		return (1);
	}
	if (argc == 5)
		j[5] = -1;
	if (j[1] == 1)
		printf("%ld 1 died\n", j[2]);
	else
		fill_my_philo_args(data, j);
	return (0);
}
