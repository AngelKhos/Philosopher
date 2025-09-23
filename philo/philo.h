/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:02:22 by authomas          #+#    #+#             */
/*   Updated: 2025/09/23 18:53:31 by authomas         ###   ########lyon.fr   */
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
	int				id;
	int				eat_counter;
	pthread_t		thread;
	struct timeval	last_eat;
	t_fork			*fork_left;
	t_fork			*fork_right;
	t_data			*data;
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
	struct timeval	start_time;
	pthread_mutex_t	flag_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	eat_check_mutex;
	pthread_mutex_t	last_eat_mutex;
};

////////////////////// PARSING /////////////////////

int				parsing(int ac, char **av, t_data *data);

/////////////////////// INIT ///////////////////////

int				init_data(t_data *data);
int				malloc_philo(t_data *data);
int				init_philo(t_data *data);

////////////////////// ROUTINE /////////////////////

void			*entry_point(t_philo *philo);
int				take_fork(t_fork *fork);
void			drop_fork(t_fork *fork);
void			print_state(t_philo *philo, char *s, int force);
void			end_loop(t_data *data);

/////////////////////// UTILS //////////////////////

int				ft_atoi(char *s);
unsigned int	time_diff_now(struct timeval t);
void			ft_usleep(long int milisec);
void			kill_philo(t_data *data, t_philo *philos,
					t_fork *forks, int philo_launched);

#endif