/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:03:59 by eagranat          #+#    #+#             */
/*   Updated: 2024/11/26 10:51:42 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_table		table;
	pthread_t	*thread;

	if (!ft_check_args(argc, argv))
		return (0);
	if (!init_table(&table, argv))
		return (0);
	thread = malloc(sizeof(pthread_t) * ft_atoi(argv[1]) + 1);
	if (!thread)
	{
		printf(RED"Error: Thread malloc failed\n"RST);
		return (0);
	}
	if (!routine(&table, thread))
	{
		free_all(&table, thread);
		return (0);
	}
	return (0);
}
