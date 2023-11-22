/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:55:21 by raalonso          #+#    #+#             */
/*   Updated: 2023/11/22 09:41:12 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

/*void	dinner(t_data *data)
{
	if (data->max_meals == 0)
		return (0);
	
}*/

/**
 * @file philo.c
 * @brief Implementation of the dining philosophers problem.
 *
 * This file contains the implementation of the dining philosophers problem,
 * where multiple philosophers sit around a table and alternate between thinking
 * and eating. The code includes functions for thread creation, mutex locking,
 * and data initialization.
 */
void	*waitthreads(void *data)
{
	t_data	*table;
	table = (t_data *)(data);
	printf("start%d\n", get_int(&table->mutex, &table->threads_created));
	while (get_int(&table->mutex, &table->threads_created) != 1);
	printf("end%d\n", get_int(&table->mutex, &table->threads_created));
	return (NULL);
}

void	set_long(pthread_mutex_t *mutex, long *dest, long value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

long	get_long(pthread_mutex_t *mutex, long *value)
{
	long	read;
	pthread_mutex_lock(mutex);
	read = *value;
	pthread_mutex_unlock(mutex);
	return (read);
}

void	set_int(pthread_mutex_t *mutex, int *dest, int value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

int	get_int(pthread_mutex_t *mutex, int *value)
{
	int	read;
	pthread_mutex_lock(mutex);
	read = *value;
	pthread_mutex_unlock(mutex);
	return (read);
}

int	main(int argc, char **argv)
{
	t_data data;
	
	if ((argc != 5 && argc != 6) || check_arg(argc, argv) == 1)
		error_exit("Error: Invalid arguments.");
	init_data(&data, argc, argv);
	int	i = 0;
	while (i < data.num_philos)
	{
		if (pthread_create(&data.philo[i].thread, NULL, &waitthreads, (void *)&data) != 0)
			error_exit("Error: During thread creation.");
		i++;
		usleep(50);
		printf("%d\n", i);
	}
	set_int(&data.mutex, &data.threads_created, 1);
	
	/*printf("philo %d -> forks %d %d\n", data.philo[0].id, data.philo[0].first_fork->id, data.philo[0].second_fork->id);
	printf("philo %d -> forks %d %d\n", data.philo[1].id, data.philo[1].first_fork->id, data.philo[1].second_fork->id);
	printf("philo %d -> forks %d %d\n", data.philo[2].id, data.philo[2].first_fork->id, data.philo[2].second_fork->id);
	printf("philo %d -> forks %d %d\n", data.philo[3].id, data.philo[3].first_fork->id, data.philo[3].second_fork->id);*/
	//dinner(&data);
}