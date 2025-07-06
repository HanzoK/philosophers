/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 19:28:51 by hanjkim           #+#    #+#             */
/*   Updated: 2025/03/09 16:29:35 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Helper function to initialize a philosopher's data */
void	init_philosopher_info(t_data *data, int index)
{
	data->philosopher[index].display_id = index + 1;
	data->philosopher[index].philo_id = index;
	data->philosopher[index].data = data;
	data->philosopher[index].remaining_meals = data->num_times_to_eat;
}

/* Helper function to join all previously created threads upon failure */
void	join_created_threads(t_data *data, pthread_t *threads,
							int created_count)
{
	int	j;

	j = 0;
	(void)data;
	while (j < created_count)
	{
		pthread_join(threads[j], NULL);
		j++;
	}
}

/* Main function that creates philosopher threads */
int	create_philosopher_threads(t_data *data, pthread_t *threads)
{
	int	i;
	int	result;

	i = 0;
	while (i < data->num_philosophers)
	{
		init_philosopher_info(data, i);
		result = pthread_create(&threads[i], NULL, philosopher_thread_routine,
				&data->philosopher[i]);
		if (result != 0)
		{
			write(2, "Error: Failed to create thread\n", 31);
			pthread_mutex_lock(&data->monitor);
			data->game_over = true;
			data->simulation_started = true;
			pthread_mutex_unlock(&data->monitor);
			join_created_threads(data, threads, i);
			return (1);
		}
		i++;
	}
	return (0);
}

void	join_philosopher_threads(pthread_t *threads, int num_philosophers)
{
	int	i;

	i = 0;
	while (i < num_philosophers)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
