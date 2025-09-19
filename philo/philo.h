/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:02:22 by authomas          #+#    #+#             */
/*   Updated: 2025/09/19 19:58:08 by authomas         ###   ########lyon.fr   */
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

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				bool;
}	t_fork;

typedef struct s_data	t_data;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	t_fork		*fork_left;
	t_fork		*fork_right;
	t_data		*data;
}	t_philo;

struct s_data
{
	int				time_to_death;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_number;
	int				philo_number;
	int				flag;
	t_philo			*philos;
	t_fork			*forks;
	pthread_mutex_t	flag_mutex;
};

////////////////////// PARSING /////////////////////

int		parsing(int ac, char **av, t_data *data);

/////////////////////// INIT ///////////////////////

int		init_data(t_data *data);
int		malloc_philo(t_data *data);
int		init_philo(t_data *data);

////////////////////// ROUTINE /////////////////////

void	*entry_point(t_philo *philo);

/////////////////////// UTILS //////////////////////

int		ft_atoi(char *s);

#endif