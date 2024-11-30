/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 07:24:39 by eagranat          #+#    #+#             */
/*   Updated: 2024/11/30 13:55:45 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_init(t_global *g, t_philo **philos, t_fork **forks)
{
	t_philo	*philo;
	int		i;

	*philos = (t_philo *)malloc(sizeof(t_philo) * g->a.n_philo);
	*forks = (t_fork *)malloc(sizeof(t_fork) * g->a.n_philo);
	if (!philos || !forks)
		return (false);
	i = -1;
	while (++i < g->a.n_philo)
	{
		philo = &(*philos)[i];
		philo->g = g;
		philo->id = i + 1;
		philo->last_meal = get_timestamp();
		philo->loop = 0;
		philo->right_fork = &((*forks)[i]);
		philo->left_fork = &((*forks)[i + 1]);
		if (philo->id == g->a.n_philo)
			philo->left_fork = &((*forks)[0]);
		philo->right_fork_state = DOWN;
		philo->left_fork_state = DOWN;
		pthread_mutex_init(&(philo->left_fork->fork_mutex), NULL);
	}
	return (true);
}

bool	global_init(t_global *g, t_args a)
{
	g->a = a;
	g->someone_died = false;
	if (pthread_mutex_init(&(g->philo_mutex), NULL))
		return (false);
	if (pthread_mutex_init(&(g->death_mutex), NULL))
		return (false);
	if (pthread_mutex_init(&(g->print_mutex), NULL))
		return (false);
	return (true);
}

bool	args_init(t_args *a, int argc, char **argv)
{
	a->n_philo = get_input_value(argv[1]);
	a->time_to_die = get_input_value(argv[2]) * 1000;
	a->time_to_eat = get_input_value(argv[3]) * 1000;
	a->time_to_sleep = get_input_value(argv[4]) * 1000;
	a->n_loop = -2;
	if (argc == 6)
		a->n_loop = get_input_value(argv[5]);
	if (a->n_philo == -1 || a->time_to_die == -1 || a->time_to_eat \
		== -1 || a->time_to_sleep == -1 || a->n_loop == -1)
		return (false);
	return (true);
}
