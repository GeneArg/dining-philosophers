/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:06:59 by eagranat          #+#    #+#             */
/*   Updated: 2024/11/29 18:03:21 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	time;
	long long		milliseconds;

	gettimeofday(&time, NULL);
	milliseconds = (long long)time.tv_sec * 1000LL + (long long)time.tv_usec
		/ 1000;
	return (milliseconds);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_check_args_utils(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!is_digit_str(argv[i]))
		{
			printf(RED "Error: Argument %d is not a number\n" RST, i);
			return (0);
		}
		if (!is_positive_str(argv[i]))
		{
			printf(RED "Error: Argument %d is not a positive \
number or over INT_MAX\n" RST, i);
			return (0);
		}
		i++;
	}
	if (!max_thread(argv[1]))
	{
		printf(RED "Error: Too many philos\n" RST);
		return (0);
	}
	return (1);
}

int	ft_check_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf(RED "Error: Wrong number of arguments\n" RST);
		return (0);
	}
	if (!ft_check_args_utils(argv))
		return (0);
	return (1);
}
