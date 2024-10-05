/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 02:06:37 by eagranat          #+#    #+#             */
/*   Updated: 2024/10/05 16:25:57 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
#include <limits.h>
# include <sys/time.h>

# define RST "/033[0m" // reset to default color
# define RED "/033[1;31m" // bold red
# define GRN "/033[1;32m" // bold green
# define YEL "/033[1;33m" // bold yellow
# define BLU "/033[1;34m" // bold blue
# define MAG "/033[1;35m" // bold magenta
# define CYN "/033[1;36m" // bold cyan
# define WHT "/033[1;37m" // bold white

typedef struct s_table t_table;

/*FORK*/
typedef struct s_fork
{
	pthread_mutex_t	fork;
	int fork_id;
}	t_fork;

/*PHILOSOPHER*/
typedef struct s_philo
{
	int id;
	long long meals_count;
	bool full;
	long long last_meal_time; // time passed from the last meal
	t_fork *left_fork;
	t_fork *right_fork;
	pthread_t thread_id; // a philo is a thread
	t_table *table;
}	t_philo;

/*Table
./philo 5 800 200 200 [5]*/

typedef struct s_table
{
	long long philo_count;
	long long time_to_die;
	long long time_to_eat;
	long long time_to_sleep;
	long long limit_meals; // number of meals before the end of the simulation | flag if -1
	long long start_time; // time when the simulation starts
	bool end; // flag to end the simulation - philo dies or all philos are full
	t_fork *forks; //array of forks
	t_philo *philos; //array of philos
}	t_table;

/*UTILS*/
void print_error(char *str);

#endif
