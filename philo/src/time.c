/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:23:29 by raalonso          #+#    #+#             */
/*   Updated: 2023/12/29 20:58:04 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

/**
 * Initializes the time by getting the current time in milliseconds.
 * 
 * @return The current time in milliseconds.
 */
time_t	time_init(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + current_time.tv_usec / 1000);
}

/**
 * Calculates the time elapsed since the start of the simulation.
 * 
 * @param start_sim The start time of the simulation in milliseconds.
 * @return The time elapsed since the start of the simulation in milliseconds.
 */
time_t	time_from_init(long start_sim)
{
	struct timeval	current_time;
	long			timestamp;

	gettimeofday(&current_time, NULL);
	timestamp = (((current_time.tv_sec * 1000)
				+ (current_time.tv_usec / 1000)) - start_sim);
	return (timestamp);
}

/**
 * Sleeps for a specified amount of time, while checking for the occurrence of death.
 * 
 * @param time The time to sleep in milliseconds.
 * @param philo The philosopher object.
 * @return 1 if death occurs during sleep, 0 otherwise.
 */
int	precise_sleep(long time, t_philo *philo)
{
	long	start;

	start = time_init();
	while (time_from_init(start) < time)
	{
		usleep(1000);
		if (check_death(philo) == 1)
			return (1);
	}
	return (0);
}
