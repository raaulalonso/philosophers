/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:55:21 by raalonso          #+#    #+#             */
/*   Updated: 2023/11/23 21:48:33 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	eat(t_philo *philo)
{
	printf("philo %d think\n", philo->id);
	while (get_int(&philo->mutex, &philo->first_fork->taken) == 1 || get_int(&philo->mutex, &philo->second_fork->taken) == 1); // esperan para poder comer
	set_int(&philo->mutex, &philo->first_fork->taken, 1);
	set_int(&philo->mutex, &philo->second_fork->taken, 1);
	printf("philo %d eat\n", philo->id);
	usleep(100000);
	printf("philo %d sleep\n", philo->id);
	set_int(&philo->mutex, &philo->first_fork->taken, 0);
	set_int(&philo->mutex, &philo->second_fork->taken, 0);
	usleep(100000);
}

void	*dinner_sim(void *ph)
{
	t_philo	*philo;
	philo = (t_philo *)(ph);
	while (1)
	{
		eat(&*philo);
	}
	printf("lol\n");
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
	int	j = 0;
	int	i = 0;
	while (j < 2)
	{
		//printf("%d\n", i);
		if (i % 2 == 0 && j == 0)
		{
			if (pthread_create(&data.philo[i].thread, NULL, &dinner_sim, (void *)&data.philo[i]) != 0)
				error_exit("Error: During thread creation.");
		}
		else if (i % 2 != 0 && j == 1)
		{
			if (pthread_create(&data.philo[i].thread, NULL, &dinner_sim, (void *)&data.philo[i]) != 0)
				error_exit("Error: During thread creation.");
		}
		i++;
		if (i >= data.num_philos)
		{
			j++;
			i = 0;
		}
		usleep(200);
	}
	pthread_join(data.philo[0].thread, NULL);
	

	
}