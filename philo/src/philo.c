/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:55:21 by raalonso          #+#    #+#             */
/*   Updated: 2023/11/21 23:15:09 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

/*void	dinner(t_data *data)
{
	if (data->max_meals == 0)
		return (0);
	
}*/

void	*waitthreads(void *data)
{
	t_data *table;
	printf("lol\n");
	table = &*(t_data *)data;
	while (table->threads_created != 1); //geters and setters with mutex
	
	return (NULL);
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
		if (pthread_create(&data.philo[i].thread, NULL, &waitthreads, NULL) != 0)
			error_exit("Error: During thread creation.");
		i++;
	}
	data.threads_created = 1;
	
	/*printf("philo %d -> forks %d %d\n", data.philo[0].id, data.philo[0].first_fork->id, data.philo[0].second_fork->id);
	printf("philo %d -> forks %d %d\n", data.philo[1].id, data.philo[1].first_fork->id, data.philo[1].second_fork->id);
	printf("philo %d -> forks %d %d\n", data.philo[2].id, data.philo[2].first_fork->id, data.philo[2].second_fork->id);
	printf("philo %d -> forks %d %d\n", data.philo[3].id, data.philo[3].first_fork->id, data.philo[3].second_fork->id);*/
	//dinner(&data);
}