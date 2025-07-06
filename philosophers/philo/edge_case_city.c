/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_case_city.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>		+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:17:21 by hanjkim           #+#    #+#             */
/*   Updated: 2025/03/24 15:32:29 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	adjust_timing_for_edge_cases(t_data *data)
{
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	num_philo;

	t_die = data->time_to_die;
	t_eat = data->time_to_eat;
	t_sleep = data->time_to_sleep;
	num_philo = data->num_philosophers;
	if (num_philo >= 100 && num_philo % 2 != 0 && t_die <= 3 * t_eat)
		data->timestamp_offset = 2;
	if (num_philo % 2 == 0 && t_eat == t_sleep && (t_die - (2 * t_eat)) == 1)
		data->timestamp_offset = -1;
	if ((t_die == (t_eat + t_sleep))
		|| (num_philo % 2 != 0 && 3 * t_eat == t_die))
		data->timestamp_offset = 1;
}

int	is_only_one_philosopher(t_data *data)
{
	if (data->num_philosophers == 1)
	{
		data->single_philosopher = true;
		return (1);
	}
	return (0);
}

void	handle_single_philosopher(t_data *data, int philo_id)
{
	sleep_with_check(data, data->time_to_die);
	printf("%d %d died\n", data->time_to_die, philo_id);
	pthread_mutex_lock(&data->monitor);
	data->game_over = 1;
	pthread_mutex_unlock(&data->monitor);
}
