/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 23:22:48 by mpierrot          #+#    #+#             */
/*   Updated: 2024/05/25 02:05:26 by mpierrot         ###   ########.fr       */
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

t_data	parsing_args(int argc, char **arg)
{
	int		i;
	long	j[6];
	size_t	len;
	t_data	data;

	data.is_args_ok = 0;
	if (ft_check_numbers(arg) == -1)
		data.is_args_ok = -1;
	i = 0;
	while (arg[i] && data.is_args_ok == 0)
	{
		arg[i] = noptozero(arg[i]);
		len = ft_strlen(arg[i]);
		j[i] = ft_atol(arg[i]);
		if ((len > 11 || !len) && (j[i] > 2147483647 || j[i] < -2147483648))
			return (data);
		if ((len > 11 || !len) || (j[i] > 2147483647 || j[i] < -2147483648))
			return (data);
		i++;
	}
	if (data.is_args_ok == -1)
		return (data);
	if (argc == 5)
		j[5] = -1;
	return (fill_my_philo_args(j));
}
