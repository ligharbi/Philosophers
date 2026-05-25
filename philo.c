/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligharbi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 18:19:28 by ligharbi          #+#    #+#             */
/*   Updated: 2026/05/20 18:23:32 by ligharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*int	start_simulation(t_data *data, t_philo *philosophers)
{
	int	i;

	pthread_mutex_lock(&data->simulation_mutex);
	data->simulation_running = 1;
	pthread_mutex_unlock(&data->simulation_mutex);
	i = 0;
	while (i < data->num_philosophers)
	{
		philosophers[i].last_meal_time = data->start_time;
		if (pthread_create(&philosophers[i].thread, NULL,
				life_philosophy, &philosophers[i]) != 0)
		{
			printf("Error: Failed to create thread for philosopher %d\n",
				philosophers[i].id);
			free_all(philosophers, data);
			return (1);
		}
		if (data->num_philosophers % 2 == 0)
			usleep(1000);
		else
			usleep(2000);
		i++;
	}
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_join(philosophers[i].thread, NULL);
		i++;
	}
	return (0);
}*/

static int	create_threads(t_data *data, t_philo *philosophers)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		philosophers[i].last_meal_time = data->start_time;
		if (pthread_create(&philosophers[i].thread, NULL,
				life_philosophy, &philosophers[i]) != 0)
		{
			printf("Error: Failed to create thread for philosopher %d\n",
				philosophers[i].id);
			free_all(philosophers, data);
			return (1);
		}
		if (data->num_philosophers % 2 == 0)
			usleep(1000);
		else
			usleep(2000);
		i++;
	}
	return (0);
}

static void	join_threads(t_data *data, t_philo *philosophers)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_join(philosophers[i].thread, NULL);
		i++;
	}
}

int	start_simulation(t_data *data, t_philo *philosophers)
{
	pthread_mutex_lock(&data->simulation_mutex);
	data->simulation_running = 1;
	pthread_mutex_unlock(&data->simulation_mutex);
	if (create_threads(data, philosophers))
		return (1);
	join_threads(data, philosophers);
	return (0);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
