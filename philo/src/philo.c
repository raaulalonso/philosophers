/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:55:21 by raalonso          #+#    #+#             */
/*   Updated: 2024/01/09 19:36:54 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

/**
 * @brief Simulates a philosopher having dinner.
 * 
 * This function represents the dinner routine of a philosopher. 
 * It performs the following steps:
 * 2. Prints the current status as "THINK".
 * 3. Takes the forks to start eating.
 * 4. If the maximum number of meals is defined, increments the meal counter
 * 	  and checks if it has reached the maximum.
 * 5. Prints the current status as "EAT".
 * 6. Updates the time of the last meal.
 * 7. Sleeps for the specified time to eat.
 * 8. Prints the current status as "SLEEP".
 * 9. Releases the forks after set to SLEEP to avoid other filosophers taking
 * 	  forks early.
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
	set_int(&philo->first_fork->mutex, &philo->first_fork->taken, 0);
	set_int(&philo->second_fork->mutex, &philo->second_fork->taken, 0);
	if (precise_sleep(philo->data->time_to_sleep, philo) == 1)
		return ;
}

/**
 * @brief Simulates the dinner for a philosopher.
 * 
 * This function is responsible for simulating the dinner for a philosopher.
 * 
 * The `t_philo` structure contains information about the philosopher and the 
 * simulation data.
 * 
 * The function updates the `time_last_meal` field of the `t_philo` structure
 * and calls the `dinner` function.
 * 
 * The simulation continues until the `get_int` function returns 1, indicating 
 * that the simulation should stop. (Philosopher death or max meals reached)
 * 
 * @param ph A pointer to a `t_philo` structure representing the philosopher.
 * @return void* Always returns NULL.
 */
void	*sim(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)(ph);
	philo->time_last_meal = philo->data->start_sim;
	while (get_int(&philo->data->mutex, &philo->data->dead) != 1)
	{
		dinner(&*philo);
	}
	return (NULL);
}

/**
 * Creates a thread for a philosopher.
 * 
 * @param data The data structure containing the philosopher information.
 * @param i The index of the philosopher.
 */
void	thread_creation(t_data *data, int i)
{
	if (pthread_create(&data->philo[i].thread, NULL,
			&sim, (void *)&data->philo[i]) != 0)
		error_exit("Error: During thread creation.");
}

/**
 * @brief This function creates and manages the threads for the philosophers.
 * 
 * The function loops through the philosophers and creates threads for the 
 * even and odd philosophers separately.
 * 
 * It first creates threads for the even philosophers and then for the odd 
 * philosophers.
 * This is to avoid deadlock when taking the forks.
 * 
 * @param data A pointer to the data structure containing information about 
 * the philosophers.
 */
void	threads_loop(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < 2)
	{
		if (i % 2 == 0 && j == 0)
			thread_creation(data, i);
		else if (i % 2 != 0 && j == 1)
			thread_creation(data, i);
		i++;
		if (i >= data->num_philos)
		{
			j++;
			i = 0;
		}
		usleep(100);
	}
}

/**
 * @brief The main function of the program.
 *
 * This function is the entry point of the program. It initializes the data 
 * structure, checks the command-line arguments, starts the simulation, and
 * waits for all threads to finish before exiting.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of strings containing the command-line arguments.
 * @return The exit status of the program.
 */
int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	i = 0;
	if ((argc != 5 && argc != 6) || check_arg(argc, argv) == 1)
		error_exit("Error: Invalid arguments.");
	init_data(&data, argc, argv);
	data.start_sim = time_init();
	threads_loop(&data);
	while (i < data.num_philos)
	{
		pthread_join(data.philo[i].thread, NULL);
		i++;
	}
	free_data(&data);
	return (0);
}
