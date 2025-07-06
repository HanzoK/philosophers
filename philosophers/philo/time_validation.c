/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:21:41 by hanjkim           #+#    #+#             */
/*   Updated: 2025/03/20 16:18:13 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_current_time(void)
{
	long			current_time;
	struct timeval	time;
	int				ret;

	ret = gettimeofday(&time, NULL);
	if (ret == -1)
	{
		write(2, "Error: gettimeofday failed\n", 27);
		return (-1);
	}
	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (current_time);
}

int	get_time_error_check(t_data *data, long time)
{
	if (time < 0)
	{
		pthread_mutex_lock(&data->monitor);
		data->game_over = true;
		pthread_mutex_unlock(&data->monitor);
		return (1);
	}
	return (0);
}

void	compute_timestamp(t_data *data, long	*timestamp)
{
	long	current_time;

	current_time = get_current_time();
	if (current_time < 0)
	{
		*timestamp = 0;
		get_time_error_check(data, current_time);
		return ;
	}
	*timestamp = get_current_time() - data->start_time;
}

void	sleep_with_check(t_data *data, long sleep_time)
{
	long	start_time;
	long	current_time;

	start_time = get_current_time();
	if (get_time_error_check(data, start_time))
		return ;
	current_time = start_time;
	while (current_time - start_time < sleep_time)
	{
		pthread_mutex_lock(&data->monitor);
		if (data->game_over)
		{
			pthread_mutex_unlock(&data->monitor);
			return ;
		}
		pthread_mutex_unlock(&data->monitor);
		usleep(100);
		current_time = get_current_time();
		if (get_time_error_check(data, current_time))
			return ;
	}
}
