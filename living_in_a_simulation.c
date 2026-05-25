/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living_in_a_simulation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligharbi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 18:17:38 by ligharbi          #+#    #+#             */
/*   Updated: 2026/05/20 18:18:43 by ligharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_simulation_runnig(t_data *data)
{
	bool	running;

	pthread_mutex_lock(&data->simulation_mutex);
	running = data->simulation_running;
	pthread_mutex_unlock(&data->simulation_mutex);
	return (running);
}

bool	set_simulation_running(t_data *data, bool value)
{
	pthread_mutex_lock(&data->simulation_mutex);
	data->simulation_running = value;
	pthread_mutex_unlock(&data->simulation_mutex);
	return (value);
}

void	eat(t_philo *ph)
{
	take_forks(ph);
	mutexed_printf(ph, "is eating");
	pthread_mutex_lock(&ph->data->meals_mutex);
	ph->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&ph->data->meals_mutex);
	if (ph->data->num_meals > 0)
		ph->meals_eaten++;
	usleep(ph->data->time_to_eat * 1000);
	pthread_mutex_unlock(&ph->data->forks[ph->left_fork]);
	pthread_mutex_unlock(&ph->data->forks[ph->right_fork]);
}

void	sleep_think(t_philo *ph)
{
	mutexed_printf(ph, "is sleeping");
	usleep(ph->data->time_to_sleep * 1000);
	if (!fammish(ph))
		mutexed_printf(ph, "is thinking");
}
