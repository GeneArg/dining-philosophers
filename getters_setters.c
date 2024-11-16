/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 10:31:03 by eagranat          #+#    #+#             */
/*   Updated: 2024/11/16 23:47:27 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*TO AVOID WRITING LOCK UNLOCK EVERYWHERE*/

void	set_bool(t_mtx *mtx, bool *var, bool value)
{
	safe_mutex(mtx, LOCK);
	*var = value;
	safe_mutex(mtx, UNLOCK);
}

bool	get_bool(t_mtx *mtx, bool *var)
{
	bool value;

	safe_mutex(mtx, LOCK);
	value = *var;
	safe_mutex(mtx, UNLOCK);
	return (value);
}

long get_long(t_mtx *mtx, long *var)
{
	long value;

	safe_mutex(mtx, LOCK);
	value = *var;
	safe_mutex(mtx, UNLOCK);
	return (value);
}

void set_long(t_mtx *mtx, long *var, long value)
{
	safe_mutex(mtx, LOCK);
	*var = value;
	safe_mutex(mtx, UNLOCK);
}

bool simulation_end(t_table *table)
{
	bool end_status = get_bool(&table->table_mutex, &table->end);
	return end_status;
}

