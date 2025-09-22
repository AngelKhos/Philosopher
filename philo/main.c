/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:02:00 by authomas          #+#    #+#             */
/*   Updated: 2025/09/22 13:17:42 by authomas         ###   ########lyon.fr   */
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
	usleep(80000);
	gettimeofday(&data->start_time, NULL);
	pthread_mutex_unlock(&data->flag_mutex);
}

int	is_dead(t_philo *philo, t_data *data)
{
	struct timeval t;
	unsigned int res;

	gettimeofday(&t, NULL);
	pthread_mutex_lock(&data->last_eat_mutex);
    res = (t.tv_sec - philo->last_eat.tv_sec) * 1000 +
		(t.tv_usec - philo->last_eat.tv_usec) / 1000;
	pthread_mutex_unlock(&data->last_eat_mutex);
	if ((int)res > data->time_to_death)
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
	int i;
	int finish;
	int finish_eating;

	i = 0;
	finish_eating = 0;
	while (data->flag != 1)
	{
		finish = 1;
		i = 0;
		usleep(10000);
		while (i < data->philo_number && finish_eating == 0)
		{
			if (is_dead(&data->philos[i], data))
			{
				print_state(&data->philos[i], "has died");
				finish_eating = 1;
				end_loop(data);
				break ;
			}
			eat_check(data, &data->philos[i], &finish);
		}
		if (finish == 1)
			end_loop(data);
	}
}


void kill_philo(t_data *data, t_philo *philos, t_fork *forks)
{
	int i;

	i = 0;
	while (i < data->philo_number)
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
	check_philo(data);
	// print_data(data);
	kill_philo(data, data->philos, data->forks);
	free(data);
	return (0);
}
