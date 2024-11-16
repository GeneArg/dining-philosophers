/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 07:24:39 by eagranat          #+#    #+#             */
/*   Updated: 2024/11/16 11:23:44 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int philo_nbr;

	philo_nbr = philo->table->philo_nbr;

	if (philo_position % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
	}
	else
	{
		philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
		philo->second_fork = &forks[philo_position];
	}
}

static void philo_init(t_table *table)
{
	int i;
	t_philo *philo;

	i = 0;
	while (i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_count = 0;
		philo->table = table;

		assign_forks(philo, table->forks, i);
	}
}

void	data_init(t_table *table)
{
	int i;

	i = 0;
	table->end = false;
	table->all_threads_ready = false;
	table->philos = protect_malloc(sizeof(t_philo) * table->philo_nbr);
	safe_mutex(&table->table_mutex, INIT);
	table->forks = protect_malloc(sizeof(t_fork) * table->philo_nbr);
	while (i < table->philo_nbr)
	{
		safe_mutex(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
}
