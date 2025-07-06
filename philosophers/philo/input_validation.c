/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:27:03 by hanjkim           #+#    #+#             */
/*   Updated: 2025/03/24 14:54:56 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	validate_arg_count(int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf("Error: Are you sure you know what you're doing?\n");
		printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat\
time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	return (0);
}

int	skip_spaces_and_plus(char *str, int start)
{
	int	j;

	j = start;
	while (str[j] == ' ' || str[j] == '\t')
		j++;
	if (str[j] == '+')
		j++;
	while (str[j] == ' ' || str[j] == '\t')
		j++;
	return (j);
}

int	validate_numbers(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = 0;
		if (argv[i][0] == '\0')
			return (printf("Bruh.\n"), 1);
		j = skip_spaces_and_plus(argv[i], j);
		if (argv[i][j] == '\0')
			return (printf("Bruh.\n"), 1);
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] == ' ' || argv[i][j] == '\t')
			{
				j++;
				continue ;
			}
			if (!ft_isdigit(argv[i][j]))
				return (printf("Oh come on. + numbers only, dude.\n"), 1);
			j++;
		}
	}
	return (0);
}

int	validate_range(int argc, char **argv)
{
	int				i;
	unsigned int	value;

	i = 1;
	while (i < argc)
	{
		value = ft_atol(argv[i]);
		if (value < 1 || value >= INT_MAX - 1)
		{
			printf("One who tests too much, tests his own sanity. \
~Confucius, 2025\n");
			printf("Also, input must be between 1 and 2147483647\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	validate_input(int argc, char **argv)
{
	if (validate_arg_count(argc))
		return (1);
	if (validate_numbers(argc, argv))
		return (1);
	if (validate_range(argc, argv))
		return (1);
	return (0);
}
