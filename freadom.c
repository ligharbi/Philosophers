/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freadom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligharbi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 12:41:05 by ligharbi          #+#    #+#             */
/*   Updated: 2026/05/20 12:43:29 by ligharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_the_thinkers(t_philo *philosophers)
{
	if (!philosophers)
		return (1);
	free(philosophers);
	return (0);
}

int	free_the_forks(t_data *data)
{
	int	i;

	if (!data || !data->forks)
		return (1);
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	data->forks = NULL;
	return (0);
}

int	free_all(t_philo *philosophers, t_data *data)
{
	if (!data)
		return (1);
	free_the_forks(data);
	free_the_thinkers(philosophers);
	if (data)
	{
		pthread_mutex_destroy(&data->print_mutex);
		pthread_mutex_destroy(&data->meals_mutex);
		pthread_mutex_destroy(&data->simulation_mutex);
		pthread_mutex_destroy(&data->death_mutex);
		free(data);
	}
	return (0);
}
