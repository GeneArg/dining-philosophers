/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 14:29:28 by eagranat          #+#    #+#             */
/*   Updated: 2024/11/16 14:58:57 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	write_status_debug(t_philo_status status, t_philo *philo, long elapsed_time)
{
	if (status == TAKE_FIRST_FORK && !simulation_end(philo->table))
		printf(WHT"%-6ld"RST" %d has taken the first fork\n", elapsed_time, philo->id);
	else if (status == TAKE_SECOND_FORK && !simulation_end(philo->table))
		printf(WHT"%-6ld"RST" %d has taken the second fork\n", elapsed_time, philo->id);
	else if (status == EATING && !simulation_end(philo->table))
		printf(WHT"%-6ld"CYN" %d is eating\n", elapsed_time, philo->id);
	else if (status == SLEEPING && !simulation_end(philo->table))
		printf(WHT"%-6ld"RST" %d is sleeping\n", elapsed_time, philo->id);
	else if (status == THINKING && !simulation_end(philo->table))
		printf(WHT"%-6ld"RST" %d is thinking\n", elapsed_time, philo->id);
	else if (status == DEAD && !simulation_end(philo->table))
		printf(RED"%-6ld %d died\n"RST, elapsed_time, philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long elapsed_time;

	elapsed_time = get_time(MILLISECONDS) - philo->table->start_time;
	if (philo->full)
		return ;
	safe_mutex(&philo->table->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed_time);
	else
	{
		if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK) && !simulation_end(philo->table))
			printf(WHT"%-6ld"RST" %d has taken a fork\n", elapsed_time, philo->id);
		else if (status == EATING && !simulation_end(philo->table))
			printf(WHT"%-6ld"CYN" %d is eating\n", elapsed_time, philo->id);
		else if (status == SLEEPING && !simulation_end(philo->table))
			printf(WHT"%-6ld"RST" %d is sleeping\n", elapsed_time, philo->id);
		else if (status == THINKING && !simulation_end(philo->table))
			printf(WHT"%-6ld"RST" %d is thinking\n", elapsed_time, philo->id);
		else if (status == DEAD && !simulation_end(philo->table))
			printf(RED"%-6ld %d died\n"RST, elapsed_time, philo->id);
	}
	safe_mutex(&philo->table->write_mutex, UNLOCK);
}
