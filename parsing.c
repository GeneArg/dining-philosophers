/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:18:34 by eagranat          #+#    #+#             */
/*   Updated: 2024/10/05 17:40:40 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

static const char *valid_input(const char *str)
{
	int len;
	const char *number;

	len = 0;
	while (is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			print_error("Only positive numbers are allowed.\n");
		str++;
	}
	if (!is_digit(*str))
		print_error("The input is not a digit\n");
	number = str;
	while (is_digit(*str))
	{
		len++;
		str++;
	}
	if (len > 10)
		print_error("The number is over INT_MAX.\n");
	return (number);
}


/*1. Actual numbers
 * 2. not > INT_MAX
 * 3. timestamps > 60ms*/

static long ft_atol(const char *str)
{
	long number;

	number = 0;
	str = valid_input(str);
	while (is_digit(*str))
	{
		number = number * 10 + (*str - '0');
		str++;
	}
	if (number > INT_MAX)
		print_error("The number is over INT_MAX.\n");
	return (number);
}

void	parse_input(t_table *table, char *argv[])
{
	table->philo_count = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1000;
	table->time_to_eat = ft_atol(argv[3]) * 1000;
	table->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (table->time_to_die < 60000 || table->time_to_eat < 60000 || table->time_to_sleep < 60000)
		print_error("The time is less than 60ms.\n");
	if (argv[5])
	{
		table->limit_meals = ft_atol(argv[5]);
		if (table->limit_meals < 1)
			print_error("The number of meals is less than 1.\n");
	}
	else
		table->limit_meals = -1;
	if (table->philo_count < 2)
		print_error("The number of philosophers is less than 2.\n");
}
