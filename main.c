/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligharbi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 12:30:04 by ligharbi          #+#    #+#             */
/*   Updated: 2026/05/20 12:30:12 by ligharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philosophers;

	if (ac < 5 || ac > 6)
	{
		printf("Error: Invalid number of arguments\n");
		return (1);
	}
	data = init_data(ac, av);
	if (ac == 5)
		data->num_meals = -1;
	philosophers = init_philosophers(data);
	if (start_simulation(data, philosophers) != 0)
		return (1);
	free_all(philosophers, data);
	return (0);
}

void	parse_arguments(t_data *data, char **av, int ac)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (i == 1)
		{
			data->num_philosophers = ft_atoi(av[i]);
			if (data->num_philosophers <= 0)
				msg(i);
		}
		else if (i == 2)
		{
			data->time_to_die = ft_atoi(av[i]);
			if (data->time_to_die <= 0)
				msg(i);
		}
		else
			parse_arguments_div(data, av, i);
		i++;
	}
}

void	parse_arguments_div(t_data *data, char **av, int i)
{
	if (i == 3)
	{
		data->time_to_eat = ft_atoi(av[i]);
		if (data->time_to_eat <= 0)
			msg(i);
	}
	else if (i == 4)
	{
		data->time_to_sleep = ft_atoi(av[i]);
		if (data->time_to_sleep <= 0)
			msg(i);
	}
	else if (i == 5)
		data->num_meals = ft_atoi(av[i]);
}

void	msg(int i)
{
	printf("Error: Invalid argument %d\n", i);
	exit(1);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result * sign > 2147483647)
			return (-1);
		if (result * sign < -2147483648)
			return (0);
		i++;
	}
	return ((int)(result * sign));
}
