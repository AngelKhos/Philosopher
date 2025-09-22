/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 18:57:39 by authomas          #+#    #+#             */
/*   Updated: 2025/09/22 13:34:14 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		get_flag(t_data *data)
{
	int ret;

	ret = 1;
	pthread_mutex_lock(&data->flag_mutex);
	if (data->flag == 1)
		ret = 0;
	pthread_mutex_unlock(&data->flag_mutex);
	return (ret);
}

void	print_state(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (get_flag(philo->data))
		printf("%u %d %s\n", time_diff_now(philo->data->start_time), philo->id, s);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	thinking_state_odd(t_philo *philo)
{
	print_state(philo, "is thinking");
	while (take_fork(philo->fork_right) == 0 && get_flag(philo->data))
		usleep(100);
	print_state(philo, "has taken a fork");
	while (take_fork(philo->fork_left) == 0 && get_flag(philo->data))
		usleep(100);
	print_state(philo, "has taken a fork");
}

void	thinking_state_even(t_philo *philo)
{
	print_state(philo, "is thinking");
	while (take_fork(philo->fork_left) == 0 && get_flag(philo->data))
		usleep(100);
	print_state(philo, "has taken a fork");
	while (take_fork(philo->fork_right) == 0 && get_flag(philo->data))
		usleep(100);
	print_state(philo, "has taken a fork");
}	

void	routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		thinking_state_even(philo);
	else
		thinking_state_odd(philo);
	gettimeofday(&philo->last_eat, NULL);
	print_state(philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	drop_fork(philo->fork_right);
	drop_fork(philo->fork_left);
	if (philo->eat_counter != -1)
		philo->eat_counter--;
	print_state(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

void	*entry_point(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->flag_mutex);
	pthread_mutex_unlock(&philo->data->flag_mutex);
	gettimeofday(&philo->last_eat, NULL);
	if (philo->id % 2 != 0)
		usleep(philo->data->time_to_eat);
	if (philo->id == 1)
		usleep(1000);
	while (get_flag(philo->data))
	{
		routine(philo);
	}
	return (0);
}
