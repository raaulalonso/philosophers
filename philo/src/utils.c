/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 20:24:18 by raalonso          #+#    #+#             */
/*   Updated: 2023/11/21 20:24:36 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

static long	ft_number(const char *str, int i)
{
	int		j;
	long	num;

	j = 0;
	num = 0;
	while ((str[i + j] != '\0')
		&& ((str[i + j] <= '9') && (str[i + j] >= '0')))
	{
		num = ((num * 10) + (str[i + j] - 48));
		j++;
	}
	return (num);
}

long	ft_atoi(const char *str)
{
	int		i;
	long	num;
	int		sign;

	i = 0;
	num = 0;
	sign = 0;
	while (((str[i] > 8) && (str[i] < 14)) || (str[i] == 32))
		i++;
	if (str[i] == '-')
	{
		i++;
		sign++;
	}
	else if (str[i] == '+')
		i++;
	num = ft_number(str, i);
	if (sign == 1)
		return (num * -1);
	return (num);
}

int	check_arg(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (j < argc)
	{
		while (argv[j][i] != '\0')
		{
			if (argv[j][i] > '9' || argv[j][i] < '0')
			{
				return (1);
			}
			i++;
		}
		i = 0;
		j++;
	}
	return (0);
}

void	error_exit(char *message)
{
	printf("%s\n", message);
	exit(1);
}
