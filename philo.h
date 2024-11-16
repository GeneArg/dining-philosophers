/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 02:06:37 by eagranat          #+#    #+#             */
/*   Updated: 2024/11/16 23:26:29 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>
# include <errno.h>

# define RST "\033[0m" // reset to default color
# define RED "\033[1;31m" // bold red
# define GRN "\033[1;32m" // bold green
# define YEL "\033[1;33m" // bold yellow
# define BLU "\033[1;34m" // bold blue
# define MAG "\033[1;35m" // bold magenta
# define CYN "\033[1;36m" // bold cyan
# define WHT "\033[1;37m" // bold white

#define DEBUG_MODE 0

typedef struct s_table t_table;

typedef pthread_mutex_t t_mtx;

/*PHILO STATES*/
typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DEAD
}	t_philo_status;

/*CODES FOR GET TIME*/
typedef enum e_time_code
{
	SECONDS,
	MILLISECONDS,
	MICROSECONDS
}	t_time_code;

/*For Mutex*/
typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}	t_opcode;

/*FORK*/
typedef struct s_fork
{
	t_mtx	fork;
	int fork_id;
}	t_fork;

/*PHILOSOPHER*/
typedef struct s_philo
{
	int id;
	long meals_count;
	bool full;
	bool dead;
	long last_meal_time; // time passed from the last meal
	t_fork *first_fork;
	t_fork *second_fork;
	pthread_t thread_id; // a philo is a thread
	t_mtx philo_mutex; //for races with the monitor
	t_table *table;
}	t_philo;

/*Table
./philo 5 800 200 200 [5]*/

typedef struct s_table
{
	long philo_nbr;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	long limit_meals; // number of meals before the end of the simulation | flag if -1
	long start_time; // time when the simulation starts
	long threads_running_number; // number of threads running
	long full_philos_count; // number of philos that are full
	bool end; // flag to end the simulation - philo dies or all philos are full
	bool all_threads_ready; // flag to start the simulation
	pthread_t monitor; // monitor is a thread
	t_mtx table_mutex; // avoid race condition
	t_mtx write_mutex;
	t_fork *forks; //array of forks
	t_philo *philos; //array of philos
}	t_table;

/*UTILS*/
void print_error(char *str);
void	wait_all_threads(t_table *table);
long	get_time(t_time_code time_code);
void	presice_usleep(long usec, t_table *table);
bool all_threads_running(t_mtx *mtx, long *threads, long philo_nbr);
void increase_long(t_mtx *mtx, long *var);
void clean(t_table *table);
void	desync_philos(t_philo *philo);

/*INIT*/
void	data_init(t_table *table);

/*MONITOR*/
void	monitor_dinner(void *data);

/*SAFETY*/
void *protect_malloc(size_t size);
void safe_mutex(t_mtx *mtx, t_opcode opcode);
void safe_thread(pthread_t *thread, void (*foo)(void *), void *data, t_opcode opcode);

/*PARSING*/
void	parse_input(t_table *table, char *argv[]);

/*GETTERS_SETTERS*/
void	set_bool(t_mtx *mtx, bool *var, bool value);
bool	get_bool(t_mtx *mtx, bool *var);
long get_long(t_mtx *mtx, long *var);
void set_long(t_mtx *mtx, long *var, long value);
bool	simulation_end(t_table *table);

/*WRITE*/
void	write_status(t_philo_status status, t_philo *philo, bool debug);

/*DINNER*/
void	dinner_start(t_table *table);
void	dinner_simulation(void *data);
void lone_philo(void *arg);
void thinking(t_philo *philo, bool pre_simulation);

#endif
