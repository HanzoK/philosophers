/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:16:37 by hanjkim           #+#    #+#             */
/*   Updated: 2025/03/24 14:46:26 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
// #include <stdint.h>

typedef struct s_philosopher
{
	int				philo_id;
	int				remaining_meals;
	int				display_id;
	struct s_data	*data;
}				t_philosopher;

typedef struct s_data
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	monitor;
	pthread_mutex_t	eat;
	bool			infinite_eating;
	bool			game_over;
	bool			single_philosopher;
	bool			simulation_started;
	long			start_time;
	long			*last_meal_times;
	int				timestamp_offset;
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_to_eat;
	t_philosopher	*philosopher;
}				t_data;

//game_over_status
bool	get_game_over(t_data *data);
void	set_game_over(t_data *data, bool status);

//philosopher_utils.c
int		ft_isdigit(char c);
int		ft_isinrange(int n);
int		ft_atol(char *str);
int		ft_strlen(char *str);

//input_validation.c
int		validate_arg_count(int argc);
int		validate_numbers(int argc, char **argv);
int		validate_range(int argc, char **argv);
int		validate_input(int argc, char **argv);

//edge_case_city.c
void	adjust_timing_for_edge_cases(t_data *data);
int		is_only_one_philosopher(t_data *data);
void	handle_single_philosopher(t_data *data, int philo_id);

//simulation_preparation.c
void	initialize_simulation_elements(t_data *data, char **argv);
int		init_forks(t_data *data);
int		init_last_meal_times(t_data *data);
int		init_mutexes(t_data *data);

//time_validation.c
long	get_current_time(void);
int		get_time_error_check(t_data *data, long time);
void	compute_timestamp(t_data *data, long	*timestamp);
void	sleep_with_check(t_data *data, long sleep_time);

//run_simulation.c
int		allocate_memory(t_data *data, pthread_t **philosopher_threads);
int		prepare_mut_and_pthreads(t_data *data, pthread_t *philosopher_threads);
int		start_monitoring(t_data *data, pthread_t *monitor_thread);
void	join_and_cleanup(t_data *data,
			pthread_t *philosopher_threads, pthread_t monitor_thread);
void	run_simulation(t_data *data);

//fork_management.c
void	lock_forks(t_data *data, int philo_index, int philo_id);
void	unlock_forks(t_data *data, int philo_index);

//philosopher_actions.c
void	print_action(t_data *data, char *action, int philo_id);
void	perform_eating(t_data *data, int philo_index, int philo_id);
void	perform_sleeping(t_data *data, int philo_id);
void	perform_thinking(t_data *data, int philo_id);

//philosopher_actions_utils.c
void	decrement_meal_count(t_data *data, int philo_index);

//thread_routine.c
void	*monitor_thread_routine(void *arg);
void	*philosopher_thread_routine(void *arg);

//thread_management.c
int		create_philosopher_threads(t_data *data, pthread_t *threads);
void	join_philosopher_threads(pthread_t *threads, int num_philosophers);

//monitor_philos.c
int		have_all_philosophers_eaten(t_data *data);
int		check_philosopher_starvation(t_data *data, int philo_index);
int		check_all_philosophers_status(t_data *data);
void	*monitor_philosophers(void *arg);

// freedom.c
void	annihilate_mutexes(t_data *data);
void	free_everything(t_data *data, pthread_t *thread);
