/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:31:36 by eagranat          #+#    #+#             */
/*   Updated: 2024/11/26 22:32:30 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_table *table, t_philo *current_philo)
{
	if (!table || !current_philo)
		return ;
	pthread_mutex_lock(&current_philo->right_fork);
	pthread_mutex_lock(&current_philo->next->right_fork);
	if (!check_first_meal(table, current_philo))
	{
		pthread_mutex_unlock(&current_philo->next->right_fork);
		pthread_mutex_unlock(&current_philo->right_fork);
		return ;
	}
	pthread_mutex_lock(&table->is_thinking);
	if (table->dinner_end)
	{
		pthread_mutex_unlock(&current_philo->next->right_fork);
		pthread_mutex_unlock(&current_philo->right_fork);
		pthread_mutex_unlock(&table->is_thinking);
		return ;
	}
	eating_utils(table, current_philo);
	pthread_mutex_unlock(&current_philo->next->right_fork);
	pthread_mutex_unlock(&current_philo->right_fork);
}

void	sleeping(t_table *table, t_philo *current_philo)
{
	long long	current_time;
	long long	dinner_start;
	int			index;

	if (table->dinner_end)
		return ;
	pthread_mutex_lock(&table->is_thinking);
	if (table->dinner_end)
	{
		pthread_mutex_unlock(&table->is_thinking);
		return ;
	}
	current_time = get_time();
	dinner_start = table->dinner_start;
	index = current_philo->index;
	printf("%llu %d is sleeping\n", current_time - dinner_start, index);
	pthread_mutex_unlock(&table->is_thinking);
	usleep(current_philo->time_to_sleep * 1000);
	current_philo->is_sleeping = false;
	current_philo->is_thinking = true;
}

void	thinking(t_table *table, t_philo *current_philo)
{
	long long	current_time;
	long long	dinner_start;
	int			index;

	pthread_mutex_lock(&table->is_thinking);
	if (table->dinner_end)
	{
		pthread_mutex_unlock(&table->is_thinking);
		return ;
	}
	current_time = get_time();
	dinner_start = table->dinner_start;
	index = current_philo->index;
	printf("%llu %d is thinking\n", current_time - dinner_start, index);
	pthread_mutex_unlock(&table->is_thinking);
	if (table->nbr_of_philo % 2 != 0)
		usleep(current_philo->time_to_eat * 1000);
	current_philo->is_thinking = false;
	current_philo->is_eating = true;
}

void	check_death_utils(t_table *table, t_philo *current_philo,
		long long current_time)
{
	int	index;

	pthread_mutex_lock(&table->is_thinking);
	if (table->dinner_end)
	{
		pthread_mutex_unlock(&table->is_thinking);
		return ;
	}
	index = current_philo->index;
	current_philo->is_dead = true;
	printf(RED "%llu %d died\n" RST, current_time - table->dinner_start, index);
	table->dinner_end = true;
	pthread_mutex_unlock(&table->is_thinking);
}

void	check_meals_utils(t_table *table)
{
	pthread_mutex_lock(&table->is_thinking);
	if (table->dinner_end)
	{
		pthread_mutex_unlock(&table->is_thinking);
		pthread_mutex_lock(&table->death);
		return ;
	}
	table->dinner_end = true;
	pthread_mutex_unlock(&table->is_thinking);
}
