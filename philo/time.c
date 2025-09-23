/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:28:25 by authomas          #+#    #+#             */
/*   Updated: 2025/09/23 18:54:32 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	time_diff_now(struct timeval t)
{
	unsigned int	res;
	struct timeval	t_now;

	gettimeofday(&t_now, NULL);
	res = (t_now.tv_sec - t.tv_sec) * 1000000 + (t_now.tv_usec - t.tv_usec);
	return (res);
}

long int	get_time(long int first_milisec)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000000 + tv.tv_usec - first_milisec * 1000));
}

void	ft_usleep(long int milisec)
{
	long int	end_sleep;

	end_sleep = get_time(0) + milisec * 1000;
	while (get_time(0) < end_sleep)
	{
		usleep((end_sleep - get_time(0)) / 2);
	}
}
