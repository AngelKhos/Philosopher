/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:23:54 by authomas          #+#    #+#             */
/*   Updated: 2025/09/21 14:54:00 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int    take_fork(t_fork *fork)
{
	int ret;

	ret = 0;
	pthread_mutex_lock(&fork->mutex);
	if (fork->bool == 0)
	{
		fork->bool = 1;
		ret = 1;
	}
	pthread_mutex_unlock(&fork->mutex);
	return (ret);
}

void    drop_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	fork->bool = 0;
	pthread_mutex_unlock(&fork->mutex);
}
