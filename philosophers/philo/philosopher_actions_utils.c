/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:51:30 by hanjkim           #+#    #+#             */
/*   Updated: 2025/03/03 16:49:35 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	decrement_meal_count(t_data *data, int philo_index)
{
	pthread_mutex_lock(&data->monitor);
	if (data->infinite_eating == 0)
	{
		if (data->philosopher[philo_index].remaining_meals > 0)
			data->philosopher[philo_index].remaining_meals--;
	}
	pthread_mutex_unlock(&data->monitor);
}
