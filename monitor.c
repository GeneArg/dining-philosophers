/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:55:41 by eagranat          #+#    #+#             */
/*   Updated: 2024/11/16 20:34:30 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool philo_died(t_philo *philo)
{
	long elapsed_time;
	long time_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed_time = get_time(MILLISECONDS) - get_long(&philo->philo_mutex, &philo->last_meal_time);
	time_to_die = philo->table->time_to_die / 1000; // convert to milliseconds
	if (elapsed_time > time_to_die)
		return (true);
	return (false);
}

void	monitor_dinner(void *data)
{
	printf("Monitor thread initialized...\n");

	int i;
	t_table *table;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex, &table->threads_running_number, table->philo_nbr))
		; //SPINLOCK till all threads are running
	while (!simulation_end(table))
	{
		i = 0;
		while (i < table->philo_nbr && !simulation_end(table))
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->end, true);
				write_status(DEAD, table->philos + i, DEBUG_MODE);
			}
			i++;
		}
	}
}
