/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:55:21 by raalonso          #+#    #+#             */
/*   Updated: 2023/12/28 22:36:50 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	dinner(t_philo *philo)
{
	int	take;
	
	take = 0;
	if (get_int(&philo->data->mutex, &philo->data->dead) == 1) // comprobar si alguien murio
		return ;
	printf("%ldms philo %d is thinking\n",
		time_from_init(get_long(&philo->data->mutex,
				&philo->data->start_sim)), philo->id); // lo primero que hacen es pensar hasta que puedan comer. mutex podria quitarse.
	while (1) // mientras no tenga sus dos tenedores
	{
		if (get_int(&philo->first_fork->mutex, &philo->first_fork->taken) == 0)
		{
			set_int(&philo->first_fork->mutex, &philo->first_fork->taken, 1);
			take++;
			printf("%ldms philo %d has taken a fork\n",
				time_from_init(get_long(&philo->data->mutex,
						&philo->data->start_sim)), philo->id);
			if (take == 2)
				break ;
		}
		else if (get_int(&philo->second_fork->mutex, &philo->second_fork->taken) == 0)
		{
			set_int(&philo->second_fork->mutex, &philo->second_fork->taken, 1);
			take++;
			printf("%ldms philo %d has taken a fork\n",
				time_from_init(get_long(&philo->data->mutex,
						&philo->data->start_sim)), philo->id);
			if (take == 2)
				break ;
		}
		if (get_int(&philo->data->mutex, &philo->data->dead) == 1) // comprobar si alguien murio
			return ;
		else if (get_int(&philo->data->mutex, &philo->data->dead) != 1 &&
				time_from_init(philo->time_last_meal) > philo->data->time_to_die) // comprobar si ha muerto de hambre
		{
			set_int(&philo->data->mutex, &philo->data->dead, 1);
			printf("%ldms philo %d died\n",
				time_from_init(get_long(&philo->data->mutex,
						&philo->data->start_sim)), philo->id);
			return ;
		}
		usleep(100);
	}
	if (philo->meal_counter != -1) // si se ha definido el numero de comidas maximas, se cuentan las comidas y se comprueba si ha llegado a la maxima.
	{
		philo->meal_counter++;
		if (philo->meal_counter == philo->data->max_meals + 1)
		{
			philo->data->dead = 1;
			return ;
		}
	}
	printf("%ldms philo %d is eating\n", time_from_init(get_long(&philo->data->mutex, &philo->data->start_sim)), philo->id); // come.
	philo->time_last_meal = time_init(); // se actualiza la ultima vez que comio
	precise_sleep(philo->data->time_to_eat, philo); // come durante este tiempo.
	if (get_int(&philo->data->mutex, &philo->data->dead) == 1) // comprobar si alguien murio
		return ;
	printf("%ldms philo %d is sleeping\n", time_from_init(get_long(&philo->data->mutex, &philo->data->start_sim)), philo->id); // duerme.
	set_int(&philo->mutex, &philo->first_fork->taken, 0); // suelta sus tenedores despues de decir que esta durmiendo para no solapar los mensajes.
	set_int(&philo->mutex, &philo->second_fork->taken, 0);
	precise_sleep(philo->data->time_to_sleep, philo); // duerme durante este tiempo.
	// mientras duerme deberia comprobar si se ha muerto de hambre.
}

void	precise_sleep(long time, t_philo *philo)
{
	long start;

	start = time_init();
	while (time_from_init(start) < time)
	{
		usleep(1000);
	}
}

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

time_t	time_init()
{
	struct	timeval current_time;

	gettimeofday(&current_time, NULL);
	return((current_time.tv_sec * 1000) + current_time.tv_usec / 1000);
}

time_t time_from_init(long start_sim)
{
	struct	timeval current_time;
	long	timestamp;

	gettimeofday(&current_time, NULL);
	timestamp = (((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000)) - start_sim);
	return (timestamp);
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