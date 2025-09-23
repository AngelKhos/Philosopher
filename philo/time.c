/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:28:25 by authomas          #+#    #+#             */
/*   Updated: 2025/09/23 14:11:02 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int time_diff(struct timeval t_1, struct timeval t_2)
{
    unsigned int res;

    res = (t_2.tv_sec - t_1.tv_sec) * 1000 + (t_2.tv_usec - t_1.tv_usec) / 1000;
    return (res);
}

unsigned int time_diff_now(struct timeval t)
{
    unsigned int res;
    struct timeval t_now;
    
    gettimeofday(&t_now, NULL);
    res = (t_now.tv_sec - t.tv_sec) * 1000 + (t_now.tv_usec - t.tv_usec) / 1000;
    return (res);
}

long int    get_time(long int first_milisec)
{
    struct timeval    tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000 + tv.tv_usec / 1000 - first_milisec));
}

void    ft_usleep(long int milisec)
{
    long int    end_sleep;

    end_sleep = get_time(0) + milisec;
    while (get_time(0) < end_sleep)
    {
        usleep(333);
    }
}

