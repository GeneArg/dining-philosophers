/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:03:59 by eagranat          #+#    #+#             */
/*   Updated: 2024/11/29 18:03:04 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_table *table)
{
	pthread_mutex_destroy(&table->is_thinking);
	pthread_mutex_destroy(&table->is_sleeping);
	pthread_mutex_destroy(&table->meal_count_lock);
	pthread_mutex_destroy(&table->death);
}

void	free_list(t_philo **philo)
{
	t_philo	*current;
	t_philo	*next;

	current = *philo;
	if (!current)
		return ;
	while (1)
	{
		next = current->next;
		pthread_mutex_destroy(&current->right_fork);
		free(current);
		if (next == *philo)
			break ;
		current = next;
	}
	*philo = NULL;
}

void	free_all(t_table *table, pthread_t *thread)
{
	destroy_mutexes(table);
	free(thread);
	free_list(&table->philo);
}

int	main(int argc, char **argv)
{
	t_table		table;
	pthread_t	*thread;

	if (!ft_check_args(argc, argv))
		return (0);
	if (!init_table(&table, argv))
		return (0);
	thread = malloc(sizeof(pthread_t) * (ft_atoi(argv[1]) + 1));
	if (!thread)
	{
		printf(RED "Error: Thread malloc failed\n" RST);
		return (0);
	}
	if (!routine(&table, thread))
	{
		free_all(&table, thread);
		return (0);
	}
	return (0);
}
