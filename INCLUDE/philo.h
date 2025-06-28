/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokim2 <jisokim2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:35:02 by jisokim2          #+#    #+#             */
/*   Updated: 2025/06/28 15:22:28 by jisokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>
#include <pthread.h>

#define YELLOW	"\033[0;33m"
#define ORANGE	"\033[38;5;214m"
#define GREEN	"\033[0;32m"
#define BLUE    "\033[0;34m"
#define RED     "\033[0;31m" 
#define DEFAULT   "\033[0m"
#define ERROR	-1
#define INT_MAX	2147483647
#define INT_MIN	-2147483648

typedef struct s_table
{
	int				philo_num;
	long long		time_to_die;
	long long		time_to_sleep;
	long long		time_to_eat;
	long long		start_time;
	int				must_eat_counts;
	bool			someone_died;
	struct s_philo	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	shutdown_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	monitor;
	bool			monitor_flag;
	bool			eat_mutex_flag;
	bool			print_mutex_flag;
	bool			shut_down_mutex_flag;
	bool			*forks_mutex_flag;
}	t_table;

typedef struct s_philo
{
	t_table			*table;
	pthread_t		thread;
	long long		last_meal_time;
	unsigned int	id;
	int				eat_counts;
	int				left_fork;
	int				right_fork;
}	t_philo;

//init.c
t_table		*init_table(int ac, char **av);
t_philo		*init_philo(t_table *table);
int			init_mutex(t_table *table);
int			init_mutex_flag(t_table *table);

// void	init_threads(t_table *table);
int			init_threads(t_table *table);
int			init_single_thread(t_table *table);

//utils.c
void		blocking_time(time_t ms, t_philo *philo);
long long	get_ms_time(void);
void		safe_print(t_philo *philo, int id, const char *s, long long time);
// t_state	get_philo_state(t_philo *philo);
// void	set_philo_state (t_philo *philo, t_state state);

//philo_single.c
void		*philo_single(void *data);

//thread_routine.c
void		*philo_routine(void *data);
bool		try_take_forks(t_philo *philo);
void		eat(t_philo *philo);
void		philo_sleep(t_philo *philo);

//thread_routine_helper.c
void		set_fork_order(t_philo *philo, int *first, int *second);
bool		take_fork(t_philo *philo, int fork_idx, const char *msg);
void		putdown_forks(t_philo *philo);
void		putdown_onefork(pthread_mutex_t *fork1);

//monitor.c
// void	*monitor_routine(void *data);
int			should_stop(t_philo *philo);
bool		is_full(t_philo *philo);
bool		is_someone_dead(t_philo *philo);

//parsing.c
bool		is_valid(int ac, char **av);
int			ft_atoi(char *str);

//free.c
void		all_free(t_table *table);
void		join_threads(t_table *table);