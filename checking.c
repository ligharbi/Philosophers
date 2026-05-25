/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligharbi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 12:39:40 by ligharbi          #+#    #+#             */
/*   Updated: 2026/05/20 12:40:44 by ligharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	fammish(t_philo *ph)
{
	long long	current_time;
	long long	last_meal;

	current_time = get_time_ms();
	pthread_mutex_lock(&ph->data->meals_mutex);
	last_meal = ph->last_meal_time;
	pthread_mutex_unlock(&ph->data->meals_mutex);
	if (current_time - last_meal > ph->data->time_to_die)
		return (true);
	return (false);
}

bool	check_meals(t_philo *ph)
{
	int	meals;

	pthread_mutex_lock(&ph->data->meals_mutex);
	meals = ph->meals_eaten;
	pthread_mutex_unlock(&ph->data->meals_mutex);
	if (ph->data->num_meals > 0 && meals >= ph->data->num_meals)
		return (true);
	return (false);
}
