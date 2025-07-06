/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 19:00:02 by hanjkim           #+#    #+#             */
/*   Updated: 2025/03/19 21:47:08 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor_thread_routine(void *arg)
{
	t_data	*data;
	int		game_over;
	int		condition_met;

	data = (t_data *)arg;
	game_over = 0;
	condition_met = 0;
	while (1)
	{
		pthread_mutex_lock(&data->monitor);
		game_over = data->game_over;
		pthread_mutex_unlock(&data->monitor);
		if (game_over == true)
			break ;
		condition_met = check_all_philosophers_status(data);
		if (condition_met == true)
		{
			pthread_mutex_lock(&data->monitor);
			data->game_over = true;
			pthread_mutex_unlock(&data->monitor);
			break ;
		}
		usleep(99);
	}
	return (NULL);
}

/* Wait until the simulation has started or game_over is set.
   Returns true if the simulation started, false otherwise. */
bool	wait_for_simulation_start(t_data *data)
{
	bool	sim_started;

	pthread_mutex_lock(&data->monitor);
	while (data->simulation_started == false && data->game_over == false)
	{
		pthread_mutex_unlock(&data->monitor);
		usleep(99);
		pthread_mutex_lock(&data->monitor);
	}
	sim_started = data->simulation_started;
	pthread_mutex_unlock(&data->monitor);
	return (sim_started);
}

/* Check if the simulation should terminate.
   Returns true if game_over is set or if there is only one philosopher.
   In the latter case, it also handles the single philosopher scenario. */
bool	check_termination_conditions(t_data *data, int philo_id)
{
	bool	game_over;

	pthread_mutex_lock(&data->monitor);
	game_over = data->game_over;
	pthread_mutex_unlock(&data->monitor);
	if (game_over)
		return (true);
	if (is_only_one_philosopher(data))
	{
		handle_single_philosopher(data, philo_id);
		return (true);
	}
	return (false);
}

/* Perform one cycle of philosopher actions */
void	philosopher_cycle(t_data *data, int philo_index, int philo_id)
{
	lock_forks(data, philo_index, philo_id);
	perform_eating(data, philo_index, philo_id);
	decrement_meal_count(data, philo_index);
	unlock_forks(data, philo_index);
	perform_sleeping(data, philo_id);
	perform_thinking(data, philo_id);
}

/* The main philosopher thread routine */
void	*philosopher_thread_routine(void *arg)
{
	t_philosopher	*philo;
	t_data			*data;
	int				philo_index;
	int				philo_id;

	philo = (t_philosopher *)arg;
	data = philo->data;
	philo_index = philo->philo_id;
	philo_id = philo->display_id;
	if (!wait_for_simulation_start(data))
		return (NULL);
	while (1)
	{
		if (check_termination_conditions(data, philo_id))
			break ;
		philosopher_cycle(data, philo_index, philo_id);
	}
	return (NULL);
}
