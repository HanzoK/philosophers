/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 13:42:58 by hanjkim           #+#    #+#             */
/*   Updated: 2025/06/27 21:52:25 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Allocate memory for philosopher threads and philosopher data
int	allocate_memory(t_data *data, pthread_t **philosopher_threads)
{
	*philosopher_threads = malloc(sizeof(pthread_t) * data->num_philosophers);
	if (!*philosopher_threads)
		return (1);
	data->philosopher = malloc(sizeof(t_philosopher) * data->num_philosophers);
	if (data->philosopher == NULL)
	{
		free(*philosopher_threads);
		return (1);
	}
	return (0);
}

// Initialize mutexes and create philosopher threads
int	prepare_mut_and_pthreads(t_data *data, pthread_t *philosopher_threads)
{
	int	res;

	res = init_mutexes(data);
	if (res != 0)
		return (res);
	res = create_philosopher_threads(data, philosopher_threads);
	return (res);
}

// Start the simulation by signaling and creating the monitor thread
int	start_monitoring(t_data *data, pthread_t *monitor_thread)
{
	int	res;

	pthread_mutex_lock(&data->monitor);
	data->simulation_started = true;
	pthread_mutex_unlock(&data->monitor);
	res = pthread_create(monitor_thread, NULL, monitor_thread_routine, data);
	return (res);
}

// Join monitor thread, join philosopher threads, clean up resources
void	join_and_cleanup(t_data *data,
			pthread_t *philosopher_threads, pthread_t monitor_thread)
{
	pthread_join(monitor_thread, NULL);
	join_philosopher_threads(philosopher_threads, data->num_philosophers);
	annihilate_mutexes(data);
	free_everything(data, philosopher_threads);
}

// Main simulation runner that ties the above steps together
void	run_simulation(t_data *data)
{
	pthread_t	monitor_thread;
	pthread_t	*philosopher_threads;

	if (allocate_memory(data, &philosopher_threads))
		return ;
	if (prepare_mut_and_pthreads(data, philosopher_threads))
		return ((void)0, free_everything(data, philosopher_threads));
	if (start_monitoring(data, &monitor_thread))
	{
		free_everything(data, philosopher_threads);
		return ;
	}
	join_and_cleanup(data, philosopher_threads, monitor_thread);
}
