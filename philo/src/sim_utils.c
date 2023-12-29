/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:20:10 by raalonso          #+#    #+#             */
/*   Updated: 2023/12/29 20:52:12 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

/**
 * @brief Prints the status of a philosopher.
 * 
 * This function prints the status of a philosopher based on the given print parameter.
 * The status can be one of the following: THINK, EAT, SLEEP, FORK, or DIED.
 * The function calculates the time elapsed since the start of the simulation using the time_from_init function.
 * The philosopher's ID is also printed along with the status.
 * 
 * @param print The status to be printed (THINK, EAT, SLEEP, FORK, or DIED).
 * @param philo Pointer to the philosopher structure.
 */
void	print_status(t_print print, t_philo *philo)
{
	if (print == THINK)
	{
		printf("%ldms philo %d is thinking\n", time_from_init(get_long
				(&philo->data->mutex, &philo->data->start_sim)), philo->id);
	}
	else if (print == EAT)
	{
		printf("%ldms philo %d is eating\n", time_from_init(get_long
				(&philo->data->mutex, &philo->data->start_sim)), philo->id);
	}
	else if (print == SLEEP)
	{
		printf("%ldms philo %d is sleeping\n", time_from_init(get_long
				(&philo->data->mutex, &philo->data->start_sim)), philo->id);
	}
	else if (print == FORK)
	{
		printf("%ldms philo %d has taken a fork\n", time_from_init(get_long
				(&philo->data->mutex, &philo->data->start_sim)), philo->id);
	}
	else if (print == DIED)
	{
		printf("%ldms philo %d died\n", time_from_init(get_long
				(&philo->data->mutex, &philo->data->start_sim)), philo->id);
	}
}

/**
 * @brief if a philosopher has died either due to starvation or by another philosopher.
 * 
 * It checks if any philosopher has died by acquiring the dead flag using the mutex.
 * Also checks if the philosopher has died of starvation by comparing the time since their last meal
 * with the time_to_die value.
 * If the philosopher has died of starvation, it sets the dead flag to 1 and prints the status.
 * 
 * @param philo The philosopher to check.
 * @return 1 if the philosopher has died, 0 otherwise.
 */
int	check_death(t_philo *philo)
{
	if (get_int(&philo->data->mutex, &philo->data->dead) == 1)
		return (1);
	else if (get_int(&philo->data->mutex, &philo->data->dead) != 1
		&& time_from_init(philo->time_last_meal) > philo->data->time_to_die)
	{
		set_int(&philo->data->mutex, &philo->data->dead, 1);
		print_status(DIED, philo);
		return (1);
	}
	return (0);
}

/**
 * @brief Takes the forks for a philosopher.
 * 
 * This function attempts to take the forks for a philosopher.
 * It checks if the first fork is available, and if so, takes it.
 * Then it checks if the second fork is available, and if so, takes it.
 * If both forks are successfully taken, the function returns 0.
 * If the philosopher dies while attempting to take the forks, the function returns 1.
 * 
 * @param philo Pointer to the philosopher structure.
 * @return 0 if the forks are successfully taken, 1 if the philosopher dies.
 */
int	take_forks(t_philo *philo)
{
	int	take;

	take = 0;
	while (1)
	{
		if (get_int(&philo->first_fork->mutex, &philo->first_fork->taken) == 0)
		{
			set_int(&philo->first_fork->mutex, &philo->first_fork->taken, 1);
			take++;
			print_status(FORK, philo);
		}
		else if (get_int(&philo->second_fork->mutex, &philo->second_fork->taken) == 0)
		{
			set_int(&philo->second_fork->mutex, &philo->second_fork->taken, 1);
			take++;
			print_status(FORK, philo);
		}
		if (take == 2)
			break ;
		if (check_death(philo) == 1)
			return (1);
		usleep(100);
	}
	return (0);
}
