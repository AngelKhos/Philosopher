/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:02:00 by authomas          #+#    #+#             */
/*   Updated: 2025/09/24 15:56:04 by authomas         ###   ########lyon.fr   */
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

int	launch_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->flag_mutex);
	while (i < data->philo_number && data->flag == 0)
	{
		if (pthread_create(&philo[i].thread, NULL,
				(void *(*)(void *))entry_point, &data->philos[i]))
		{
			printf("Error: pthread_create broke :(\n");
			data->flag = 1;
			break ;
		}
		i++;
	}
	usleep(80000);
	gettimeofday(&data->start_time, NULL);
	pthread_mutex_unlock(&data->flag_mutex);
	return (i);
}

int	is_dead(t_philo *philo, t_data *data)
{
	struct timeval	t;
	unsigned int	res;

	gettimeofday(&t, NULL);
	pthread_mutex_lock(&data->last_eat_mutex);
	res = (t.tv_sec - philo->last_eat.tv_sec) * 1000000
		+ (t.tv_usec - philo->last_eat.tv_usec);
	pthread_mutex_unlock(&data->last_eat_mutex);
	if ((int)res / 1000 > data->time_to_death)
		return (1);
	return (0);
}

void	eat_check(t_data *data, t_philo *philo, int *finish)
{
	pthread_mutex_lock(&data->eat_check_mutex);
	if (philo->eat_counter != 0)
		*finish = 0;
	pthread_mutex_unlock(&data->eat_check_mutex);
}

void	check_philo(t_data *data)
{
	int	i;
	int	finish;

	i = 0;
	while (data->flag != 1)
	{
		finish = 1;
		i = 0;
		while (i < data->philo_number)
		{
			if (is_dead(&data->philos[i], data))
			{
				pthread_mutex_lock(&data->flag_mutex);
				print_state(&data->philos[i], "died", 1);
				data->flag = 1;
				pthread_mutex_unlock(&data->flag_mutex);
				break ;
			}
			eat_check(data, &data->philos[i], &finish);
			i++;
		}
		if (finish == 1)
			end_loop(data);
		usleep(10);
	}
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		philo_launched;

	data = malloc(sizeof(t_data));
	if (!init_data(data))
		return (1);
	if (!parsing(ac, av, data))
		return (1);
	if (!malloc_philo(data))
	{
		free(data);
		return (1);
	}
	if (!init_philo(data))
		return (1);
	philo_launched = launch_philo(data, data->philos);
	if (philo_launched == data->philo_number)
	{
		ft_usleep(data->time_to_death / 2);
		check_philo(data);
	}
	kill_philo(data, data->philos, data->forks, philo_launched);
	free(data);
	return (0);
}
