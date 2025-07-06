/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:17:01 by hanjkim           #+#    #+#             */
/*   Updated: 2025/03/24 14:51:16 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Check if a character is a digit */
int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/* Check if number is within range */
int	ft_isinrange(int n)
{
	if (n >= 0 && n <= 2147483647)
		return (1);
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atol(char *str)
{
	int	num;
	int	i;
	int	digit;

	num = 0;
	i = 0;
	digit = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		digit = str[i] - '0';
		if (num > (INT_MAX - digit) / 10)
			return (-1);
		num = num * 10 + digit;
		i++;
	}
	return (num);
}
