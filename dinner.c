/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:04:53 by eagranat          #+#    #+#             */
/*   Updated: 2024/11/29 18:26:14 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_actions(t_table *table, t_philo *current_philo)
{
	if (!table || !current_philo)
		return ;
	while (1)
	{
		pthread_mutex_lock(&table->death);
		if (table->dinner_end)
		{
			pthread_mutex_unlock(&table->death);
			break ;
		}
		pthread_mutex_unlock(&table->death);
		if (current_philo->is_eating)
			eating(table, current_philo);
		else if (current_philo->is_sleeping)
			sleeping(table, current_philo);
		else if (current_philo->is_thinking)
			thinking(table, current_philo);
	}
}

int	check_if_one(t_table *table, t_philo *current_philo)
{
	long long	dinner_start;

	pthread_mutex_lock(&table->death);
	if (table->nbr_of_philo == 1)
	{
		pthread_mutex_lock(&table->is_thinking);
		usleep(current_philo->time_to_die * 1000);
		current_philo->is_dead = true;
		dinner_start = table->dinner_start;
		printf("%llu %d has taken a fork\n", get_time() - dinner_start,
			current_philo->index);
		printf(RED "%llu %d died\n" RST, get_time() - dinner_start,
			current_philo->index);
		table->dinner_end = true;
		pthread_mutex_unlock(&table->is_thinking);
		pthread_mutex_unlock(&table->death);
		return (1);
	}
	pthread_mutex_unlock(&table->death);
	return (0);
}

void	philo_routine_utils(t_table *table)
{
	// long long	dinner_start;

	pthread_mutex_lock(&table->is_thinking);
	table->dinner_start = get_time();
	//dinner_start = table->dinner_start;
	// printf("dinner started at %llu\n", get_time() - dinner_start);
	pthread_mutex_unlock(&table->is_thinking);
}

void	*philo_routine(void *arg)
{
	t_philo	*current_philo;
	t_table	*table;

	table = (t_table *)arg;
	if (!table)
		return (NULL);
	pthread_mutex_lock(&table->is_sleeping);
	current_philo = table->philo;
	while ((current_philo->index) != table->philo_index + 1)
		current_philo = current_philo->next;
	table->philo_index++;
	if ((current_philo->index % 2 != 0)
		&& (current_philo->index != table->nbr_of_philo))
		current_philo->is_eating = true;
	else
		current_philo->is_thinking = true;
	if (current_philo->index == 1)
		philo_routine_utils(table);
	pthread_mutex_unlock(&table->is_sleeping);
	if (check_if_one(table, current_philo))
		return (NULL);
	philo_actions(table, current_philo);
	return (NULL);
}

int	routine(t_table *table, pthread_t *thread)
{
	int	i;

	i = 0;
	if (pthread_create(&thread[table->nbr_of_philo], NULL, monitor_routine,
			(void *)table))
	{
		printf(RED "Error: Can't create philo thread\n" RST);
		return (0);
	}
	usleep(100);
	while (i < table->nbr_of_philo)
	{
		if (pthread_create(&thread[i], NULL, philo_routine, (void *)table))
		{
			printf(RED "Error: Can't create philo thread\n" RST);
			return (0);
		}
		i++;
	}
	i = 0;
	while (i <= table->nbr_of_philo)
		pthread_join(thread[i++], NULL);
	free_all(table, thread);
	return (1);
}
