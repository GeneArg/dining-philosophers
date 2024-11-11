/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:04:53 by eagranat          #+#    #+#             */
/*   Updated: 2024/11/11 22:19:23 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dinner_start(t_table *table)
{
	int i;

	i = 0;
	if (table->limit_meals == 0)
		return ;
	else if (table->limit_meals == 1)
		// TODO
	else
		while (i < table->philo_nbr)
		{
			safe_thread(&table->philos[i].thread_id, dinner_simulation, &table->philos[i], CREATE); // TODO
			i++;
		}
}
