/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:55:41 by eagranat          #+#    #+#             */
/*   Updated: 2024/11/16 23:54:36 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool philo_died(t_philo *philo)
{
	long current_time = get_time(MILLISECONDS);
	long last_meal_time = get_long(&philo->philo_mutex, &philo->last_meal_time);

	// Check if the philosopher has died
	return (current_time - last_meal_time >= philo->table->time_to_die ||
			get_bool(&philo->philo_mutex, &philo->dead));
}



void monitor_dinner(void *data)
{
	t_table *table;
	int i;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex, &table->threads_running_number, table->philo_nbr))
		;
	while (!simulation_end(table))
	{
		i = 0;
		while (i < table->philo_nbr && !simulation_end(table))
		{
			if (philo_died(&table->philos[i]))
			{
				set_bool(&table->table_mutex, &table->end, true);
				write_status(DEAD, &table->philos[i], DEBUG_MODE);
				return;
			}
			i++;
		}
		if (table->limit_meals > 0 &&
			get_long(&table->table_mutex, &table->full_philos_count) == table->philo_nbr)
		{
			set_bool(&table->table_mutex, &table->end, true);
		}
	}
}
