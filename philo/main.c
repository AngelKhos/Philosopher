/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:02:00 by authomas          #+#    #+#             */
/*   Updated: 2025/09/19 19:43:52 by authomas         ###   ########lyon.fr   */
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

int arg_init(int ac, char **av, int *args)
{
	int i;
	int j;

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
	return(1);
}

int is_alldigits(char *s)
{
	int i;

	i = 0;
	while (s[i] == '+' || s[i] == '-')
		i++;
	while(s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int check_arg(char **av)
{
	int i;

	i = 1;
	while(av[i])
	{
		if (!is_alldigits(av[i]))
			return (0);
		i++;
	}
	return (1);
}

int parsing(int ac, char **av, t_data *data)
{
	int args[5];

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

int init_data(t_data *data)
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

void print_data(t_data *data)
{
	t_philo *philo;
	int i = 0;

	philo = data->philos;
	while (i < data->philo_number)
	{
		printf("data->philo[%d].id = %d\n",i , philo[i].id);
		i++;
	}
	printf("number of philo: %d\n", data->philo_number);
	printf("time to die: %d\n", data->time_to_death);
	printf("time to eat: %d\n", data->time_to_eat);
	printf("time to sleep: %d\n", data->time_to_sleep);
	printf("number of eating action: %d\n", data->eat_number);
}

int malloc_philo(t_data *data)
{
	t_philo *philo;
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

int init_philo(t_data *data)
{
	t_philo *philo;
	t_fork	*forks;
	int i;

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

void launch_philo(t_data *data, t_philo *philo)
{
	int i;

	i = 0;
	pthread_mutex_lock(&data->flag_mutex);
	while (i < data->philo_number && data->flag == 0)
	{
		if (pthread_create(&philo[i].thread, NULL,
			(void * (*)(void *))entry_point, &data->philos[i]))
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

int main(int ac, char **av)
{
	t_data *data;

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
