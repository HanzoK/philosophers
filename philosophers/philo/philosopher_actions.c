/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:43:08 by hanjkim           #+#    #+#             */
/*   Updated: 2025/03/20 16:18:34 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_action(t_data *data, char *action, int philo_id)
{
	long	time;

	compute_timestamp(data, &time);
	pthread_mutex_lock(&data->monitor);
	if (!data->game_over)
		printf("%ld %d %s\n", time, philo_id, action);
	pthread_mutex_unlock(&data->monitor);
}

void	perform_eating(t_data *data, int philo_index, int philo_id)
{
	print_action(data, "is eating", philo_id);
	pthread_mutex_lock(&data->eat);
	data->last_meal_times[philo_index] = get_current_time();
	pthread_mutex_unlock(&data->eat);
	sleep_with_check(data, data->time_to_eat);
}

void	perform_sleeping(t_data *data, int philo_id)
{
	print_action(data, "is sleeping", philo_id);
	sleep_with_check(data, data->time_to_sleep);
}

void	perform_thinking(t_data *data, int philo_id)
{
	long	extra_thinking_time;

	extra_thinking_time = 0;
	print_action(data, "is thinking", philo_id);
	if (data->num_philosophers % 2 != 0)
	{
		if (data->time_to_sleep >= data->time_to_eat)
			extra_thinking_time = 1;
		else
			extra_thinking_time = data->time_to_eat - data->time_to_sleep;
		sleep_with_check(data, extra_thinking_time);
	}
}
