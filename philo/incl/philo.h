/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:55:07 by raalonso          #+#    #+#             */
/*   Updated: 2023/12/28 19:57:31 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data t_data;

typedef struct s_fork
{
	int				id;
	int				taken;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philo
{
	t_data			*data;
	int				id;
	long			time_last_meal;
	int				meal_counter;
	t_fork			*second_fork;
	t_fork			*first_fork;
	pthread_t		thread;
	pthread_mutex_t	mutex;
}	t_philo;

typedef struct s_data
{
	t_philo			*philo;
	t_fork			*fork;
	long			num_philos;
	time_t			start_sim;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			max_meals;
	int				threads_created;
	int				dead;
	pthread_mutex_t	mutex;
}	t_data;

long	ft_atoi(const char *str);
int		check_arg(int argc, char **argv);
int		check_arg(int argc, char **argv);
void	error_exit(char *message);
void	init_data(t_data *data, int argc, char **argv);
int		get_int(pthread_mutex_t *mutex, int *value);
void	set_int(pthread_mutex_t *mutex, int *dest, int value);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);
long	get_long(pthread_mutex_t *mutex, long *value);
time_t	time_from_init(long start_sim);
time_t	time_init();
void	precise_sleep(long time, t_philo *philo);

#endif