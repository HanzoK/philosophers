/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_preparation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:52:07 by hanjkim           #+#    #+#             */
/*   Updated: 2025/03/08 18:55:10 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	initialize_simulation_elements(t_data *data, char **argv)
{
	int	tmp;

	data->num_philosophers = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (!argv[5])
	{
		data->infinite_eating = true;
		data->num_times_to_eat = -1;
	}
	else
	{
		tmp = ft_atol(argv[5]);
		data->num_times_to_eat = tmp;
		data->infinite_eating = false;
	}
	data->game_over = false;
	data->single_philosopher = false;
	data->timestamp_offset = 0;
	data->simulation_started = false;
}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
	if (!data->forks)
		return (1);
	while (i < data->num_philosophers)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			write(2, "Error: Mutex init failed\n", 26);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_last_meal_times(t_data *data)
{
	int	i;

	i = 0;
	data->last_meal_times = malloc(sizeof(long) * data->num_philosophers);
	if (!data->last_meal_times)
		return (1);
	while (i < data->num_philosophers)
	{
		data->last_meal_times[i] = 0;
		i++;
	}
	return (0);
}

int	init_mutexes(t_data *data)
{
	int	result;

	result = pthread_mutex_init(&data->meal_check, NULL);
	if (result)
		return (1);
	result = pthread_mutex_init(&data->eat, NULL);
	if (result)
		return (1);
	result = pthread_mutex_init(&data->monitor, NULL);
	if (result)
		return (1);
	return (0);
}
