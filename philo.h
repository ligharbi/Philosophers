/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligharbi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 18:32:24 by ligharbi          #+#    #+#             */
/*   Updated: 2026/05/20 18:32:41 by ligharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

struct	s_philo
{
	t_data			*data;
	int				id;
	int				left_fork;
	int				right_fork;
	int				meals_eaten;
	long long		last_meal_time;
	bool			is_full;
	pthread_t		thread;
	struct s_philo	*prev;
	struct s_philo	*next;
};

struct	s_data
{
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	int				meals_finished;
	bool			death;
	t_philo			*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meals_mutex;
	pthread_mutex_t	simulation_mutex;
	pthread_mutex_t	death_mutex;
	long			start_time;
	int				simulation_running;
};

void	parse_arguments_div(t_data *data, char **av, int i);
void	parse_arguments(t_data *data, char **av, int ac);
int		ft_atoi(const char *str);
void	msg(int i);
void	init_data_mutexes(t_data *data);
t_data	*init_data(int ac, char **av);
void	init_philo_div(int i, t_philo *philosophers, t_data *data);
t_philo	*init_philosophers(t_data *data);
void	*life_philosophy(void *philo);
void	lock_fork(t_philo *ph, int fork);
void	take_forks(t_philo *ph);
void	eat(t_philo *ph);
void	sleep_think(t_philo *ph);
bool	set_simulation_running(t_data *data, bool value);
bool	get_simulation_runnig(t_data *data);
void	*monitor_philosophers(void *data_ptr);
int		start_simulation(t_data *data, t_philo *philosophers);
long	get_time_ms(void);
int		free_the_thinkers(t_philo *philosophers);
int		free_the_forks(t_data *data);
int		free_all(t_philo *philosophers, t_data *data);
bool	fammish(t_philo *ph);
bool	check_meals(t_philo *ph);
void	death_message(t_philo *ph);
void	success_message(t_philo *ph);
void	print_message(t_philo *ph, char *message);
void	mutexed_printf(t_philo *ph, char *message);
int		main(int ac, char **av);

#endif
