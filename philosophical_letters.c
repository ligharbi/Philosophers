/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophical_letters.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligharbi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 18:24:22 by ligharbi          #+#    #+#             */
/*   Updated: 2026/05/20 18:27:01 by ligharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	death_message(t_philo *ph)
{
	mutexed_printf(ph, "died\n");
	set_simulation_running(ph->data, false);
}

void	success_message(t_philo *ph)
{
	mutexed_printf(ph,
		"is full.\nAll philosophers are full!\n");
	set_simulation_running(ph->data, false);
}

void	print_message(t_philo *ph, char *message)
{
	printf("%ld %d %s\n", get_time_ms() - ph->data->start_time,
		ph->id, message);
}

void	mutexed_printf(t_philo *ph, char *message)
{
	pthread_mutex_lock(&ph->data->print_mutex);
	if (get_simulation_runnig(ph->data))
		print_message(ph, message);
	pthread_mutex_unlock(&ph->data->print_mutex);
}

/*void	mutexed_printf(t_philo *ph, char *message)
{
	int	running;

	running = get_simulation_runnig(ph->data);
	pthread_mutex_lock(&ph->data->print_mutex);
	if (running)
		print_message(ph, message);
	pthread_mutex_unlock(&ph->data->print_mutex);
}*/
