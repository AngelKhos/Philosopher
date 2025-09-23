/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 18:57:39 by authomas          #+#    #+#             */
/*   Updated: 2025/09/23 14:01:23 by authomas         ###   ########lyon.fr   */
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

void	print_state(t_philo *philo, char *s, int force)
{
	if (!force)
		if (!get_flag(philo->data))
			return ;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%u %d %s\n", time_diff_now(philo->data->start_time), philo->id, s);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

// void	thinking_state_even(t_philo *philo)
// {
// 	while (take_fork(philo->fork_right) == 0 && get_flag(philo->data))
// 		usleep(100);
// 	print_state(philo, "has taken a fork", 0);
// 	while (take_fork(philo->fork_left) == 0 && get_flag(philo->data))
// 		usleep(100);
// 	print_state(philo, "has taken a fork", 0);
// }

void	thinking_state(t_philo *philo)
{
	while (take_fork(philo->fork_left) == 0)
		usleep(100);
	print_state(philo, "has taken a fork", 0);
	while (take_fork(philo->fork_right) == 0)
		usleep(100);
	print_state(philo, "has taken a fork", 0);
}	

void	routine(t_philo *philo)
{
	
	thinking_state(philo);
	print_state(philo, "is eating", 0);
	pthread_mutex_lock(&philo->data->last_eat_mutex);
	gettimeofday(&philo->last_eat, NULL);
	pthread_mutex_unlock(&philo->data->last_eat_mutex);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->eat_check_mutex);
	if (philo->eat_counter > 0)
		philo->eat_counter--;
	pthread_mutex_unlock(&philo->data->eat_check_mutex);
	drop_fork(philo->fork_right);
	drop_fork(philo->fork_left);
	print_state(philo, "is sleeping", 0);
	ft_usleep(philo->data->time_to_sleep);
	print_state(philo, "is thinking", 0);
}

void	*entry_point(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->flag_mutex);
	pthread_mutex_unlock(&philo->data->flag_mutex);
	gettimeofday(&philo->last_eat, NULL);
	print_state(philo, "is thinking", 0);
	if (philo->id % 2 != 0)
		ft_usleep(philo->data->time_to_eat / 2);
	while (get_flag(philo->data))
	{
		routine(philo);
	}
	return (0);
}
