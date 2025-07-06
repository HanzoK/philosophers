/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:32:12 by hanjkim           #+#    #+#             */
/*   Updated: 2025/06/26 22:43:25 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Helper function to safely get game_over */
bool	get_game_over(t_data *data)
{
	bool	flag;

	pthread_mutex_lock(&data->monitor);
	flag = data->game_over;
	pthread_mutex_unlock(&data->monitor);
	return (flag);
}

/* Helper function to safely set game_over */
void	set_game_over(t_data *data, bool status)
{
	pthread_mutex_lock(&data->monitor);
	data->game_over = status;
	pthread_mutex_unlock(&data->monitor);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		init_res;

	memset(&data, 0, sizeof(t_data));
	init_res = validate_input(ac, av);
	if (init_res)
		return (1);
	initialize_simulation_elements(&data, av);
	adjust_timing_for_edge_cases(&data);
	init_res = init_forks(&data);
	if (init_res)
		return (1);
	init_res = init_last_meal_times(&data);
	if (init_res)
		return (free(data.forks), 1);
	data.start_time = get_current_time();
	get_time_error_check(&data, data.start_time);
	run_simulation(&data);
	return (0);
}
