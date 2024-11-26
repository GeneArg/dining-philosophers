/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 10:31:03 by eagranat          #+#    #+#             */
/*   Updated: 2024/11/26 22:32:34 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating_utils(t_table *table, t_philo *current_philo)
{
	long long	current_time;
	long long	dinner_start;
	int			index;

	dinner_start = table->dinner_start;
	current_time = get_time();
	index = current_philo->index;
	printf("%llu %d has taken a fork\n", current_time - dinner_start, index);
	printf("%llu %d has taken a fork\n", current_time - dinner_start, index);
	printf("%llu %d is eating\n", current_time - dinner_start, index);
	pthread_mutex_unlock(&table->is_thinking);
	pthread_mutex_lock(&table->death);
	current_philo->last_meal = current_time;
	pthread_mutex_unlock(&table->death);
	usleep(current_philo->time_to_eat * 1000);
	pthread_mutex_lock(&table->meal_count_lock);
	if (table->nbr_of_meals != -1)
		current_philo->current_meal++;
	pthread_mutex_unlock(&table->meal_count_lock);
	current_philo->first_meal = false;
	current_philo->is_eating = false;
	current_philo->is_sleeping = true;
}

void	check_first_meal_utils(t_table *table, t_philo *current_philo,
		long long current_time)
{
	long long	dinner_start;

	pthread_mutex_lock(&table->is_thinking);
	dinner_start = table->dinner_start;
	current_philo->is_dead = true;
	printf(RED "%llu %d died\n" RST, current_time - dinner_start,
		current_philo->index);
	printf(RED "dinner ended at %llu\n" RST, current_time - dinner_start);
	table->dinner_end = true;
	pthread_mutex_unlock(&table->is_thinking);
}

int	check_first_meal(t_table *table, t_philo *current_philo)
{
	long long	current_time;
	int			index;

	index = current_philo->index;
	if (current_philo->first_meal && (index % 2 == 0
			|| index == table->nbr_of_philo))
	{
		current_time = get_time();
		if (current_time - table->dinner_start >= current_philo->time_to_die)
		{
			pthread_mutex_lock(&table->death);
			if (table->dinner_end)
			{
				pthread_mutex_unlock(&table->death);
				return (0);
			}
			check_first_meal_utils(table, current_philo, current_time);
			pthread_mutex_unlock(&table->death);
			return (0);
		}
	}
	return (1);
}
