/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:02:22 by authomas          #+#    #+#             */
/*   Updated: 2025/09/16 17:41:45 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_data
{
    int time_to_death;
    int time_to_eat;
    int time_to_sleep;
    int eat_number;
    int philo_number;
    
}   t_data;

int     ft_atoi(char *s);

#endif