/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:06:59 by eagranat          #+#    #+#             */
/*   Updated: 2024/11/16 19:20:36 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	desync_philos(t_philo *philo)
{
	if (philo->table->philo_nbr % 2 == 0)
	{
		if (philo->id % 2 == 0)
			presice_usleep(30000, philo->table);
	}
	else
	{
		if (philo->id % 2 == 0)
			thinking(philo, true);
	}
}

void clean(t_table *table)
{
	t_philo *philo;
	int i;

	i = 0;
	while (i < table->philo_nbr)
	{
		philo = table->philos + i;
		safe_mutex(&philo->philo_mutex, DESTROY);
		i++;
	}
	safe_mutex(&table->write_mutex, DESTROY);
	safe_mutex(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}

void	presice_usleep(long usec, t_table *table)
{
	long start_time;
	long elapsed_time;
	long remaining_time;

	start_time = get_time(MICROSECONDS);
	while (get_time(MICROSECONDS) - start_time < usec)
	{
		if (simulation_end(table))
			break ;
		elapsed_time = get_time(MICROSECONDS) - start_time;
		remaining_time = usec - elapsed_time;
		if (remaining_time < 1000)
			usleep(remaining_time / 2);
		else
		{
			while (get_time(MICROSECONDS) - start_time < usec) //SPINLOCK
				;
		}
	}
}

long	get_time(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		print_error("gettimeofday failed");
	if (time_code == SECONDS)
		return (tv.tv_sec + tv.tv_usec / 1000000);
	else if (time_code == MILLISECONDS)
		return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	else if (time_code == MICROSECONDS)
		return (tv.tv_sec * 1000000 + tv.tv_usec);
	else
		print_error("Invalid time code");
	return (2424);

}

void print_error(char *str)
{
	printf(RED"Error: %s\n"RST, str);
	exit(EXIT_FAILURE);
}

