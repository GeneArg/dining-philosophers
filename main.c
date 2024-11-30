/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:03:59 by eagranat          #+#    #+#             */
/*   Updated: 2024/11/30 13:55:41 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_args		a;
	t_global	g;
	t_philo		*philos;
	t_fork		*forks;

	if (argc < 5 || argc > 6)
		return (error_handler("Wrong number of args\n", NULL, NULL, NULL));
	if (!args_init(&a, argc, argv))
		return (error_handler("Invalid input\n", &g, NULL, NULL));
	if (!global_init(&g, a))
		return (error_handler("Mutex init failure\n", &g, NULL, NULL));
	if (!philo_init(&g, &philos, &forks))
		return (error_handler("Malloc failure\n", &g, philos, forks));
	if (!thread_handler(&g, &philos))
		return (error_handler("Some errors with threads\n", &g, philos, forks));
	return (clean_exit(&g, philos, forks));
}
