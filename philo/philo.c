/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 18:57:39 by authomas          #+#    #+#             */
/*   Updated: 2025/09/19 19:43:15 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void routine(t_philo *philo)
{

    printf("philo is = %d\n", philo->id);
}

void *entry_point(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->flag_mutex);
    pthread_mutex_unlock(&philo->data->flag_mutex);
    while(philo->data->flag != 1)
    {
        routine(philo);
    }
    return (0);
}