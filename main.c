/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:03:59 by eagranat          #+#    #+#             */
/*   Updated: 2024/11/16 21:21:37 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char *argv[])
{
	t_table table;

	if (argc == 5 || argc == 6)
	{
		parse_input(&table, argv);
		data_init(&table);
		dinner_start(&table);
		clean(&table);
	}
	else
		print_error("Wrong input.\n"GRN"Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"RST);

}
