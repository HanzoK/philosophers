/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:06:42 by hanjkim           #+#    #+#             */
/*   Updated: 2025/03/03 16:50:23 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	annihilate_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->meal_check);
	pthread_mutex_destroy(&data->monitor);
	pthread_mutex_destroy(&data->eat);
}

void	free_everything(t_data *data, pthread_t *thread)
{
	if (data->forks)
		free(data->forks);
	if (thread)
		free(thread);
	if (data->philosopher)
		free(data->philosopher);
	if (data->last_meal_times)
		free(data->last_meal_times);
}
