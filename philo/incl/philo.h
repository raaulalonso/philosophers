/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:55:07 by raalonso          #+#    #+#             */
/*   Updated: 2023/11/22 08:59:55 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_fork
{
	int				id;
	int				taken;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philo
{
	int			id;
	long		last_meal_t;
	int			meal_counter;
	t_fork		*second_fork;
	t_fork		*first_fork;
	pthread_t	thread;
}	t_philo;

typedef struct s_data
{
	t_philo			*philo;
	t_fork			*fork;
	long			num_philos;
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

#endif