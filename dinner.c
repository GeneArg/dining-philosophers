/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:04:53 by eagranat          #+#    #+#             */
/*   Updated: 2024/11/17 00:07:25 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void lone_philo(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table); // Ensure threads start together
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE); // Takes the only fork
	// Wait for time_to_die (philosopher cannot eat)
	presice_usleep(philo->table->time_to_die, philo->table);

	// Philosopher dies
	write_status(DEAD, philo, DEBUG_MODE);
	set_bool(&philo->table->table_mutex, &philo->table->end, true); // End simulation
}





void thinking(t_philo *philo, bool pre_simulation)
{
	long t_sleep;
	long t_eat;
	long t_think;

	if (!pre_simulation)
		write_status(THINKING, philo, DEBUG_MODE);
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = t_eat * 2 + t_sleep;
	if (t_think < 0)
		t_think = 0;
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	presice_usleep(t_think * 0.42, philo->table);
}

static void eat(t_philo *philo)
{
	safe_mutex(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILLISECONDS));
	philo->meals_count++;
	write_status(EATING, philo, DEBUG_MODE);
	presice_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->limit_meals > 0 && philo->meals_count == philo->table->limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	safe_mutex(&philo->first_fork->fork, UNLOCK);
	safe_mutex(&philo->second_fork->fork, UNLOCK);
}

void	dinner_simulation(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILLISECONDS));
	increase_long(&philo->table->table_mutex, &philo->table->threads_running_number);
	desync_philos(philo);
	while (!simulation_end(philo->table))
	{
		if (philo->table->limit_meals > 0 && philo->meals_count == philo->table->limit_meals)
		{
			set_bool(&philo->philo_mutex, &philo->full, true);
			increase_long(&philo->table->table_mutex, &philo->table->full_philos_count);
			break ;
		}
		eat(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		presice_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo, false);
	}
}

void dinner_start(t_table *table)
{
	int i;

	i = 0;
	if (table->philo_nbr == 1) // Single philosopher case
	{
		table->start_time = get_time(MILLISECONDS);
		safe_thread(&table->philos[0].thread_id, lone_philo, &table->philos[0], CREATE);
		set_bool(&table->table_mutex, &table->all_threads_ready, true);
		safe_thread(&table->philos[0].thread_id, NULL, NULL, JOIN);
		return;
	}
	else
	{
		while (i < table->philo_nbr)
		{
			safe_thread(&table->philos[i].thread_id, dinner_simulation, &table->philos[i], CREATE);
			i++;
		}
		safe_thread(&table->monitor, monitor_dinner, table, CREATE);
	}

	table->start_time = get_time(MILLISECONDS); // Start simulation
	set_bool(&table->table_mutex, &table->all_threads_ready, true);

	i = 0;
	while (i < table->philo_nbr)
	{
		safe_thread(&table->philos[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
	set_bool(&table->table_mutex, &table->end, true);
	safe_thread(&table->monitor, NULL, NULL, JOIN);
}
