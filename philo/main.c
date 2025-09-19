/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:02:00 by authomas          #+#    #+#             */
/*   Updated: 2025/09/19 20:01:33 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 4 or 5 args : 
//  -number of philo
//  -time to die (in ms)
//  -time to eat (in ms)
//  -time to sleep (in ms)
//  -(optional) number of time they need to eat
// each philo is identified with a number starting from 1
// they sit in circle
// if a philo dies, the message should appear less than 10 ms after

void	print_data(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = data->philos;
	while (i < data->philo_number)
	{
		printf("data->philo[%d].id = %d\n", i, philo[i].id);
		i++;
	}
	printf("number of philo: %d\n", data->philo_number);
	printf("time to die: %d\n", data->time_to_death);
	printf("time to eat: %d\n", data->time_to_eat);
	printf("time to sleep: %d\n", data->time_to_sleep);
	printf("number of eating action: %d\n", data->eat_number);
}

void	launch_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->flag_mutex);
	while (i < data->philo_number && data->flag == 0)
	{
		if (pthread_create(&philo[i].thread, NULL,
				(void *(*)(void *))entry_point, &data->philos[i]))
			data->flag = 1;
		i++;
	}
	pthread_mutex_unlock(&data->flag_mutex);
	while (i > 0)
	{
		i--;
		pthread_join(philo[i].thread, NULL);
	}
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!init_data(data))
		return (1);
	if (!parsing(ac, av, data))
		return (1);
	if (!malloc_philo(data))
		return (1);
	if (!init_philo(data))
		return (1);
	launch_philo(data, data->philos);
	print_data(data);
	free(data->philos);
	free(data->forks);
	free(data);
	return (0);
}
