/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_philosophy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligharbi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 12:31:15 by ligharbi          #+#    #+#             */
/*   Updated: 2026/05/20 18:17:13 by ligharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_all_full(t_philo *ph)
{
	int	all_full;

	all_full = 0;
	if (ph->data->num_meals > 0 && !ph->is_full && check_meals(ph))
	{
		ph->is_full = true;
		mutexed_printf(ph, "is full");
		pthread_mutex_lock(&ph->data->meals_mutex);
		ph->data->meals_finished++;
		all_full = (ph->data->meals_finished
				>= ph->data->num_philosophers);
		pthread_mutex_unlock(&ph->data->meals_mutex);
		if (all_full)
		{
			success_message(ph);
			return (1);
		}
	}
	return (0);
}

void	*life_philosophy(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (get_simulation_runnig(ph->data))
	{
		if (fammish(ph))
		{
			pthread_mutex_lock(&ph->data->death_mutex);
			ph->data->death = true;
			pthread_mutex_unlock(&ph->data->death_mutex);
			death_message(ph);
			return (NULL);
		}
		if (check_all_full(ph))
			return (NULL);
		eat(ph);
		sleep_think(ph);
	}
	return (NULL);
}

void	lock_fork(t_philo *ph, int fork)
{
	pthread_mutex_lock(&ph->data->forks[fork]);
	if (fork == ph->right_fork)
		mutexed_printf(ph, "has taken his fork");
	else
		mutexed_printf(ph, "has taken his neighbour fork");
}

void	take_forks(t_philo *ph)
{
	int	first;
	int	second;

	first = ph->left_fork;
	second = ph->right_fork;
	if (first > second)
	{
		first = ph->right_fork;
		second = ph->left_fork;
	}
	lock_fork(ph, first);
	if (ph->data->num_philosophers == 1)
	{
		usleep(ph->data->time_to_die * 1000);
		pthread_mutex_unlock(&ph->data->forks[first]);
		death_message(ph);
		return ;
	}
	lock_fork(ph, second);
}
