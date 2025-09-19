/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 19:48:54 by authomas          #+#    #+#             */
/*   Updated: 2025/09/19 20:04:00 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data)
{
	if (!data)
		return (0);
	data->philo_number = 0;
	data->time_to_death = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->eat_number = -1;
	data->flag = 0;
	pthread_mutex_init(&data->flag_mutex, NULL);
	return (1);
}

int	malloc_philo(t_data *data)
{
	t_philo	*philo;
	t_fork	*forks;

	forks = malloc(sizeof(t_fork) * data->philo_number);
	if (!forks)
		return (0);
	philo = malloc(sizeof(t_philo) * data->philo_number);
	if (!philo)
	{
		free(forks);
		return (0);
	}
	data->philos = philo;
	data->forks = forks;
	return (1);
}

int	init_philo(t_data *data)
{
	t_philo	*philo;
	t_fork	*forks;
	int		i;

	i = 0;
	philo = data->philos;
	forks = data->forks;
	while (i < data->philo_number)
	{
		pthread_mutex_init(&forks[i].mutex, NULL);
		philo[i].data = data;
		forks[i].bool = 0;
		philo[i].id = i + 1;
		philo[i].fork_right = &forks[(i + 1) % data->philo_number];
		philo[i].fork_left = &forks[i];
		i++;
	}
	return (1);
}
