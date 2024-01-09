/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 20:26:51 by raalonso          #+#    #+#             */
/*   Updated: 2024/01/09 19:56:28 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

/**
 * Assigns the forks to the philosophers.
 * 
 * Each philosopher has a first and second fork.
 * The first fork of each philosopher will be the one on its right 
 * (philo number 2 will have fork 2 as first fork)
 * The second fork will be thr one on its left
 * (philo number - 1)
 * 
 * The number 1 philosopher second fork will the last fork, and its first
 * fork will be the fork number 1. 
 * 
 * @param data Pointer to data structure.
 */
void	asign_forks(t_data *data)
{
	int	i;

	data->philo[0].first_fork = &data->fork[0];
	data->philo[0].second_fork = &data->fork[data->num_philos - 1];
	i = 1;
	while (i < data->num_philos)
	{
		data->philo[i].first_fork = &data->fork[i];
		data->philo[i].second_fork = &data->fork[i - 1];
		i++;
	}
}

/**
 * Allocates memory for all of the philosophers and initializes 
 * its values.
 * 
 * @param data Pointer to data structure.
 */
void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philo)
		error_exit("Error: Malloc failed.");
	while (i < data->num_philos)
	{
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].meal_counter = 0;
		i++;
	}
}

/**
 * Allocates memory for all of the forks and initializes 
 * its values and mutex.
 * 
 * @param data Pointer to data structure.
 */
void	init_fork(t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(t_fork) * data->num_philos);
	if (!data->num_philos)
		error_exit("Error: Malloc failed.");
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->fork[i].mutex, NULL) != 0)
			error_exit("Error: Mutex init failed.");
		data->fork[i].id = i + 1;
		data->fork[i].taken = 0;
		i++;
	}
}

/**
 * Destroy mutex from the forks and data structure, 
 * also frees philosohers and forks. 
 * 
 * @param data Pointer to data structure.
 */
void	free_data(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->mutex);
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->fork->mutex);
		i++;
	}
	free(data->philo);
	free(data->fork);
}

/**
 * Initializes the data structure with the provided arguments.
 * 
 * @param data The data structure to initialize.
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 */
void	init_data(t_data *data, int argc, char **argv)
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->threads_created = 0;
	data->dead = 0;
	if (pthread_mutex_init(&data->mutex, NULL) != 0)
		error_exit("Error: Mutex init failed.");
	if (argc == 6)
		data->max_meals = ft_atoi(argv[5]);
	else
		data->max_meals = -1;
	init_philo(&*data);
	init_fork(&*data);
	asign_forks(&*data);
}
