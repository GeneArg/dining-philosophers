/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:55:41 by eagranat          #+#    #+#             */
/*   Updated: 2024/11/27 09:56:37 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	check_meals(t_table *table)
{
	int		philos_eaten;
	t_philo	*current_philo;

	philos_eaten = 0;
	current_philo = table->philo;
	while (1)
	{
		pthread_mutex_lock(&table->meal_count_lock);
		if (current_philo->current_meal == table->nbr_of_meals)
		{
			philos_eaten++;
			if (philos_eaten == table->nbr_of_philo)
			{
				pthread_mutex_unlock(&table->meal_count_lock);
				check_meals_utils(table);
				return ;
			}
		}
		pthread_mutex_unlock(&table->meal_count_lock);
		current_philo = current_philo->next;
		if (current_philo == table->philo)
			break ;
	}
	return ;
}

void	check_death(t_table *table)
{
	t_philo		*current_philo;
	long long	current_time;
	long long	time_to_die;

	current_philo = table->philo;
	time_to_die = current_philo->time_to_die;
	while (1)
	{
		current_time = get_time();
		pthread_mutex_lock(&table->death);
		if (current_philo->last_meal && (current_time
				- current_philo->last_meal) >= time_to_die)
		{
			check_death_utils(table, current_philo, current_time);
			pthread_mutex_unlock(&table->death);
			return ;
		}
		pthread_mutex_unlock(&table->death);
		current_philo = current_philo->next;
		if (current_philo == table->philo)
			break ;
	}
	return ;
}

void	monitor_action(t_table *table)
{
	while (1)
	{
		if (table->nbr_of_meals != -1)
			check_meals(table);
		if (table->dinner_end)
			break ;
		check_death(table);
		if (table->dinner_end)
			break ;
	}
	return ;
}

void	*monitor_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	(void)table;
	pthread_mutex_lock(&table->is_thinking);
	usleep(60);
	pthread_mutex_unlock(&table->is_thinking);
	if (table->nbr_of_philo != 1)
		monitor_action(table);
	return (NULL);
}
