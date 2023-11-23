/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 20:26:51 by raalonso          #+#    #+#             */
/*   Updated: 2023/11/23 20:47:37 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

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
		data->philo[i].meal_counter = 0;
		i++;
	}
}

void	init_fork(t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(t_fork) * data->num_philos);
	if (!data->num_philos)
		error_exit("Error: Malloc failed.");
	while (i < data->num_philos)
	{
		data->fork[i].id = i + 1;
		data->fork[i].taken = 0;
		i++;
	}
}

void	init_data(t_data *data, int argc, char **argv)
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	pthread_mutex_init(&data->mutex, NULL);
	data->threads_created = 0;
	if (argc == 6)
		data->max_meals = ft_atoi(argv[5]);
	else
		data->max_meals = -1;
	init_philo(&*data);
	init_fork(&*data);
	asign_forks(&*data);
}