/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:03:59 by eagranat          #+#    #+#             */
/*   Updated: 2024/11/16 20:51:00 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char *argv[])
{
	t_table table;

	if (argc == 5 || argc == 6)
	{
		// 1. errors checking, filling the table
		parse_input(&table, argv);

		printf("Finished parsing inputs\n");

		// 2. init the table
		data_init(&table);

		printf("Parsed input and initialized data...\n");


		// 3. start dinner
		dinner_start(&table);

		printf("Simulation started\n");

		// 4. clean up - 1 philo is dead or all are full
		clean(&table);
	}
	else
	{
		print_error("Wrong input.\n"GRN"Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"RST);
	}

}
