/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:06:59 by eagranat          #+#    #+#             */
/*   Updated: 2024/11/30 15:25:28 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_timestamp(void)
{
	struct timeval	tv;
	static time_t	start_time = 0;
	time_t			current_time;

	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (start_time == 0)
		start_time = current_time;
	return (current_time - start_time);
}

int	someone_died(t_philo *philo)
{
	bool	state;

	pthread_mutex_lock(&(philo->g->death_mutex));
	state = philo->g->someone_died;
	pthread_mutex_unlock(&(philo->g->death_mutex));
	return (state);
}

int	get_input_value(char *s)
{
	int	n;

	n = -1;
	while (*s == 32)
		s++;
	if (*s == 45 || (*s != 43 && (*s < 48 || *s > 57)))
		return (n);
	if (*s == 43)
		s++;
	while (*s >= 48 && *s <= 57)
	{
		if (n == -1)
			n = 0;
		n = n * 10 + *s - 48;
		s++;
	}
	return (n);
}

int	clean_exit(t_global *g, t_philo *philo, t_fork *forks)
{
	if (g)
	{
		if (pthread_mutex_destroy(&g->death_mutex))
			return (EXIT_FAILURE);
		if (pthread_mutex_destroy(&g->philo_mutex))
			return (EXIT_FAILURE);
	}
	if (philo)
		free(philo);
	if (forks)
	{
		if (pthread_mutex_destroy(&forks->fork_mutex))
			return (EXIT_FAILURE);
		free(forks);
	}
	return (EXIT_SUCCESS);
}

int	error_handler(char *msg, t_global *g, t_philo *philo, t_fork *forks)
{
	write(2, RED_BOLD, 7);
	while (*msg)
		write(2, &*msg++, 1);
	write(2, RESET, 4);
	clean_exit(g, philo, forks);
	return (EXIT_FAILURE);
}
