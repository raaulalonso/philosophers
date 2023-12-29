/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:55:21 by raalonso          #+#    #+#             */
/*   Updated: 2023/12/29 20:36:40 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

/**
 * @brief Simulates a philosopher having dinner.
 * 
 * This function represents the dinner routine of a philosopher. It performs the following steps:
 * 2. Prints the current status as "THINK".
 * 3. Takes the forks to start eating.
 * 4. If the maximum number of meals is defined, increments the meal counter and checks if it has reached the maximum.
 * 5. Prints the current status as "EAT".
 * 6. Updates the time of the last meal.
 * 7. Sleeps for the specified time to eat.
 * 8. Prints the current status as "SLEEP".
 * 9. Releases the forks after set to SLEEP to avoid other filosophers taking forks early.
 * 10. Sleeps for the specified time to sleep.
 * 
 * @param philo A pointer to the philosopher structure.
 */
void	dinner(t_philo *philo)
{
	print_status(THINK, philo);
	if (take_forks(philo) == 1)
		return ;
	if (philo->meal_counter != -1)
	{
		philo->meal_counter++;
		if (philo->meal_counter == philo->data->max_meals + 1)
		{
			philo->data->dead = 1;
			return ;
		}
	}
	print_status(EAT, philo);
	philo->time_last_meal = time_init();
	if (precise_sleep(philo->data->time_to_eat, philo) == 1)
		return ;
	print_status(SLEEP, philo);
	set_int(&philo->mutex, &philo->first_fork->taken, 0);
	set_int(&philo->mutex, &philo->second_fork->taken, 0);
	if (precise_sleep(philo->data->time_to_sleep, philo) == 1)
		return ;
}

/**
 * @brief Simulates the dinner for a philosopher.
 * 
 * This function is responsible for simulating the dinner for a philosopher.
 * It takes a pointer to a `t_philo` structure as a parameter.
 * The `t_philo` structure contains information about the philosopher and the simulation data.
 * The function updates the `time_last_meal` field of the `t_philo` structure and calls the `dinner` function.
 * The simulation continues until the `get_int` function returns 1, indicating that the simulation should stop. (Philosopher death or max meals reached)
 * 
 * @param ph A pointer to a `t_philo` structure representing the philosopher.
 * @return void* Always returns NULL.
 */
void *sim(void *ph)
{
	t_philo *philo;

	philo = (t_philo *)(ph);
	philo->time_last_meal = philo->data->start_sim;
	while (get_int(&philo->data->mutex, &philo->data->dead) != 1)
	{
		dinner(&*philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data data;
	
	if ((argc != 5 && argc != 6) || check_arg(argc, argv) == 1)
		error_exit("Error: Invalid arguments.");
	init_data(&data, argc, argv);
	int	j = 0;
	int	i = 0;
	data.start_sim = time_init(); // timestamp inicio de la simulacion.
	while (j < 2) // el bucle da dos vueltas, primero crea los hilos pares, y luego los impares.
	{
		if (i % 2 == 0 && j == 0) // aqui crea los pares
		{
			if (pthread_create(&data.philo[i].thread, NULL, &sim, (void *)&data.philo[i]) != 0)
				error_exit("Error: During thread creation.");
		}
		else if (i % 2 != 0 && j == 1) // aqui los impares
		{
			if (pthread_create(&data.philo[i].thread, NULL, &sim, (void *)&data.philo[i]) != 0)
				error_exit("Error: During thread creation.");
		}
		i++;
		if (i >= data.num_philos) // una vez de crean todos los pares, se resetea el contador "i" y avanza uno "j", para seguir con todos los impares.
		{
			j++;
			i = 0;
		}
		usleep(100); // pequeño delay para evitar problemas.
	}
	i = 0;
	while (i < data.num_philos)
	{
		pthread_join(data.philo[i].thread, NULL);
		i++;
	}
}