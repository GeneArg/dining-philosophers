/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 10:44:15 by eagranat          #+#    #+#             */
/*   Updated: 2024/11/16 16:06:28 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_table *table)
{
	while(!get_bool(&table->table_mutex, &table->all_threads_ready));
}

bool all_threads_running(t_mtx *mtx, long *threads, long philo_nbr)
{
	bool ret;

	ret = false;
	safe_mutex(mtx, LOCK);
	if (*threads == philo_nbr)
		ret = true;
	safe_mutex(mtx, UNLOCK);
	return (ret);
}

void increase_long(t_mtx *mtx, long *var)
{
	safe_mutex(mtx, LOCK);
	(*var)++;
	safe_mutex(mtx, UNLOCK);
}
