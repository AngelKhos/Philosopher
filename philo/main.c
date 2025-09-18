/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:02:00 by authomas          #+#    #+#             */
/*   Updated: 2025/09/18 18:45:28 by authomas         ###   ########lyon.fr   */
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
	pthread_mutex_init(&data->mutex, NULL);
	return (1);
}

void print_data(t_data *data)
{
	printf("number of philo: %d\n", data->philo_number);
	printf("time to die: %d\n", data->time_to_death);
	printf("time to eat: %d\n", data->time_to_eat);
	printf("time to sleep: %d\n", data->time_to_sleep);
	printf("number of eating action: %d\n", data->eat_number);
	printf("i = %d\n", data->i);
}

void *routine(void *input)
{
	t_philo *philo;
	int i = 0;

	philo = input;
	printf("philo id = %d, %p\n", philo->id, &philo->id);
	pthread_mutex_lock(&philo->data->mutex);
	while(i++ < 1000)
		philo->data->i++;
	pthread_mutex_unlock(&philo->data->mutex);
	return (0);
}

void init_philo(t_data *data)
{
	t_philo *philo;
	int i;

	i = 0;
	philo = malloc(sizeof(t_philo) * data->philo_number);
	while (i < data->philo_number)
	{
		philo[i].id = i;
		philo[i].data = data;
		pthread_create(&philo[i].thread, NULL, routine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < data->philo_number)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
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
	data->i = 0;
	init_philo(data);
	print_data(data);
	free(data);
	return (0);
}
