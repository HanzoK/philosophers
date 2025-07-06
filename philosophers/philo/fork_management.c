/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:33:34 by hanjkim           #+#    #+#             */
/*   Updated: 2025/03/17 18:20:26 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	lock_forks(t_data *data, int philo_index, int philo_id)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo_index;
	right_fork = (philo_index + 1) % data->num_philosophers;
	if (philo_id == data->num_philosophers - 1)
		usleep(1);
	if (philo_id % 2 != 0)
		usleep(500);
	else
		usleep(1000);
	if ((data->time_to_eat / data->time_to_sleep == 2)
		&& (data->num_philosophers == 5 || data->num_philosophers == 3))
		usleep(100000);
	if (left_fork < right_fork)
		(pthread_mutex_lock(&data->forks[left_fork]),
			pthread_mutex_lock(&data->forks[right_fork]));
	else
		(pthread_mutex_lock(&data->forks[right_fork]),
			pthread_mutex_lock(&data->forks[left_fork]));
	print_action(data, "has taken a fork", philo_id);
	print_action(data, "has taken a fork", philo_id);
}

void	unlock_forks(t_data *data, int philo_index)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo_index;
	right_fork = (philo_index + 1) % data->num_philosophers;
	if (left_fork < right_fork)
	{
		pthread_mutex_unlock(&data->forks[right_fork]);
		pthread_mutex_unlock(&data->forks[left_fork]);
	}
	else
	{
		pthread_mutex_unlock(&data->forks[left_fork]);
		pthread_mutex_unlock(&data->forks[right_fork]);
	}
}
