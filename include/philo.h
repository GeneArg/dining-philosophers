/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 02:06:37 by eagranat          #+#    #+#             */
/*   Updated: 2024/11/26 11:20:22 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
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

typedef enum e_bool
{
	false = 0,
	true = 1
}	t_bool;

typedef struct s_philo
{
	int				index;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		last_meal;
	int				current_meal;
	t_bool			first_meal;
	t_bool			is_sleeping;
	t_bool			is_thinking;
	t_bool			is_eating;
	t_bool			is_dead;
	pthread_mutex_t	right_fork;
	struct s_philo	*next;
	struct s_philo	*prev;
}					t_philo;

typedef struct s_table
{
	int					nbr_of_philo;
	int					philo_index;
	int					nbr_of_meals;
	t_bool				first_meal;
	pthread_mutex_t		is_sleeping;
	pthread_mutex_t		is_thinking;
	pthread_mutex_t		meal_count_lock;
	pthread_mutex_t		death;
	long long			dinner_start;
	t_bool				dinner_end;
	t_philo				*philo;

}						t_table;

/*UTILS*/
int		ft_check_args(int argc, char **argv);
int		is_digit_str(char *str);
int		is_positive_str(char *str);
int		max_thread(char *str);
long	ft_atol(const char *str);
int		ft_atoi(const char *str);
long long get_time(void);
void	free_all(t_table *table, pthread_t *thread);
void	free_list(t_philo **philo);
void	destroy_mutexes(t_table *table);
int		ft_isdigit(int c);


/*INIT*/
int	init_table(t_table *table, char **argv);
int	create_philo_list(t_philo **philo, char **argv);
int	init_philo(t_philo *philo, char **argv, int index);
int	init_mutex(t_philo *philo);

/*MONITOR*/
void	*monitor_routine(void *arg);
void	monitor_action(t_table *table);
void	check_death(t_table *table);
void	check_meals(t_table *table);
void	check_meals_utils(t_table *table);
void	check_death_utils(t_table *table, t_philo *current_philo, long long current_time);

/*ROUTINE*/
int		routine(t_table *table, pthread_t *thread);
void	*philo_routine(void *arg);
void	philo_routine_utils(t_table *table);
int		check_if_one(t_table *table, t_philo *current_philo);
void	philo_actions(t_table *table, t_philo *current_philo);
void	eating_utils(t_table *table, t_philo *current_philo);
void	check_first_meal_utils(t_table *table, t_philo *current_philo, long long current_time);
int		check_first_meal(t_table *table, t_philo *current_philo);
void	thinking(t_table *table, t_philo *current_philo);
void	sleeping(t_table *table, t_philo *current_philo);
void	eating(t_table *table, t_philo *current_philo);

#endif
