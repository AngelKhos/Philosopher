/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 19:47:18 by authomas          #+#    #+#             */
/*   Updated: 2025/09/19 20:03:16 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arg_init(int ac, char **av, int *args)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (av[j])
	{
		args[i] = ft_atoi(av[j]);
		if (args[i] <= 0)
			return (0);
		i++;
		j++;
	}
	if (ac == 5)
		args[4] = -1;
	return (1);
}

int	is_alldigits(char *s)
{
	int	i;

	i = 0;
	while (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_arg(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!is_alldigits(av[i]))
			return (0);
		i++;
	}
	return (1);
}

int	parsing(int ac, char **av, t_data *data)
{
	int	args[5];

	if (ac != 5 && ac != 6)
	{
		printf("incorrect number of args, try again\n");
		return (0);
	}
	if (!check_arg(av))
	{
		printf("syntax error in args, try again\n");
		return (0);
	}
	if (!arg_init(ac, av, args))
	{
		printf("incorrect args, try again\n");
		return (0);
	}
	data->philo_number = args[0];
	data->time_to_death = args[1];
	data->time_to_eat = args[2];
	data->time_to_sleep = args[3];
	data->eat_number = args[4];
	return (1);
}
