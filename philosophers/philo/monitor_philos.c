/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>		+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 19:12:07 by hanjkim           #+#    #+#             */
/*   Updated: 2025/03/24 15:27:03 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	have_all_philosophers_eaten(t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (data->infinite_eating == true)
		return (0);
	pthread_mutex_lock(&data->monitor);
	while (i < data->num_philosophers)
	{
		if (data->philosopher[i].remaining_meals == 0)
			count++;
		i++;
	}
	pthread_mutex_unlock(&data->monitor);
	if (count == data->num_philosophers)
		return (1);
	else
		return (0);
}

int	check_philosopher_starvation(t_data *data, int philo_index)
{
	long	current_time;
	long	last_meal;
	long	timestamp;

	if (get_game_over(data))
		return (0);
	current_time = get_current_time();
	pthread_mutex_lock(&data->eat);
	last_meal = data->last_meal_times[philo_index];
	pthread_mutex_unlock(&data->eat);
	if (last_meal != 0 && (current_time - last_meal) >= data->time_to_die)
	{
		compute_timestamp(data, &timestamp);
		pthread_mutex_lock(&data->monitor);
		printf("%ld %d died\n", (timestamp + data->timestamp_offset),
			philo_index + 1);
		pthread_mutex_unlock(&data->monitor);
		set_game_over(data, true);
		return (1);
	}
	return (0);
}

int	check_all_philosophers_status(t_data *data)
{
	int	i;
	int	all_full;
	int	starved;

	i = 0;
	all_full = 0;
	starved = 0;
	while (i < data->num_philosophers)
	{
		if (check_philosopher_starvation(data, i))
			starved = 1;
		if (have_all_philosophers_eaten(data))
			all_full = 1;
		pthread_mutex_lock(&data->monitor);
		if (data->game_over == true)
		{
			pthread_mutex_unlock (&data->monitor);
			return (1);
		}
		pthread_mutex_unlock(&data->monitor);
		i++;
	}
	if (starved || all_full)
		return (1);
	return (0);
}

void	*monitor_philosophers(void *arg)
{
	t_data	*data;
	bool	game_over;

	data = (t_data *)arg;
	game_over = false;
	while (1)
	{
		pthread_mutex_lock(&data->monitor);
		game_over = data->game_over;
		pthread_mutex_unlock(&data->monitor);
		if (game_over == true)
			break ;
		if (check_all_philosophers_status(data))
		{
			pthread_mutex_lock(&data->monitor);
			data->game_over = true;
			pthread_mutex_unlock(&data->monitor);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}
