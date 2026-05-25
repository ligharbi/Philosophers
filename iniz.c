/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iniz.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligharbi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 18:10:16 by ligharbi          #+#    #+#             */
/*   Updated: 2026/05/20 18:35:24 by ligharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*init_data(int ac, char **av)
{
	int		i;
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		printf("Error: Memory allocation failed\n");
		return (NULL);
	}
	parse_arguments(data, av, ac);
	init_data_mutexes(data);
	data->start_time = get_time_ms();
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (data);
}

void	init_data_mutexes(t_data *data)
{
	pthread_mutex_init(&data->meals_mutex, NULL);
	pthread_mutex_lock(&data->meals_mutex);
	data->meals_finished = 0;
	pthread_mutex_unlock(&data->meals_mutex);
	pthread_mutex_init(&data->simulation_mutex, NULL);
	pthread_mutex_lock(&data->simulation_mutex);
	data->simulation_running = 1;
	pthread_mutex_unlock(&data->simulation_mutex);
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_lock(&data->death_mutex);
	data->death = false;
	pthread_mutex_unlock(&data->death_mutex);
	pthread_mutex_init(&data->print_mutex, NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
	if (!data->forks)
	{
		printf("Error: Memory allocation failed\n");
		free(data);
		exit(1);
	}
}

t_philo	*init_philosophers(t_data *data)
{
	t_philo	*philosophers;
	int		num_philosophers;
	int		i;

	i = 0;
	num_philosophers = data->num_philosophers;
	philosophers = malloc(sizeof(t_philo) * num_philosophers);
	if (!philosophers)
	{
		printf("Error: Memory allocation failed\n");
		exit(1);
	}
	while (i < num_philosophers)
	{
		init_philo_div(i, philosophers, data);
		i++;
	}
	return (philosophers);
}

void	init_philo_div(int i, t_philo *philosophers, t_data *data)
{
	philosophers[i].data = data;
	philosophers[i].id = i + 1;
	philosophers[i].meals_eaten = 0 ;
	philosophers[i].is_full = false;
	philosophers[i].right_fork = i;
	philosophers[i].left_fork = (i - 1 + data->num_philosophers)
		% data->num_philosophers;
	philosophers[i].last_meal_time = data->start_time;
	philosophers[i].prev = &philosophers[(i - 1 + data->num_philosophers)
		% data->num_philosophers];
	philosophers[i].next = &philosophers[(i + 1) % data->num_philosophers];
}
