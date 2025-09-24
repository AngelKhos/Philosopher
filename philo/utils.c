/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:33:32 by authomas          #+#    #+#             */
/*   Updated: 2025/09/23 18:53:04 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *s)
{
	int	i;
	long int	res;
	long int	sign;

	res = 0;
	i = 0;
	sign = 1;
	while (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r'))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + (s[i] - '0');
		if (res > 2147483647)
			return (0);
		i++;
	}
	return ((int)(res * sign));
}

void	end_loop(t_data *data)
{
	pthread_mutex_lock(&data->flag_mutex);
	data->flag = 1;
	pthread_mutex_unlock(&data->flag_mutex);
}

void	kill_philo(t_data *data, t_philo *philos,
			t_fork *forks, int philo_launched)
{
	int	i;

	i = 0;
	while (i < philo_launched)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	while (i)
	{
		i--;
		pthread_mutex_destroy(&forks[i].mutex);
	}
	pthread_mutex_destroy(&data->eat_check_mutex);
	pthread_mutex_destroy(&data->flag_mutex);
	pthread_mutex_destroy(&data->last_eat_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	free(philos);
	free(forks);
}
