#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>
#include <pthread.h>

#define YELLOW  "\033[0;33m"
#define	ORANGE  "\033[38;5;214m"
#define GREEN   "\033[0;32m"
#define BLUE    "\033[0;34m"
#define RED     "\033[0;31m" 
#define DEFAULT   "\033[0m"
#define ERROR	-1
#define	INT_MAX	2147483647
#define INT_MIN	-2147483648

typedef struct s_table
{
	int				philo_num;
	time_t			time_to_die;
	time_t			time_to_sleep;
	time_t			time_to_eat;
	time_t			start_time;
	int				must_eat_counts;
	bool			someone_died;
	struct s_philo	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t shutdown_mutex;
	pthread_mutex_t eat_mutex;
	bool			eat_mutex_flag;
	bool			print_mutex_flag;
	bool			shut_down_mutex_flag;
	bool			*forks_mutex_flag;
	pthread_t		monitor;
}	t_table;

typedef struct s_philo
{
	t_table			*table;
	pthread_t		thread;
	time_t			last_meal_time;
	unsigned int	id;
	int				eat_counts;
	int				left_fork;
	int				right_fork;
}	t_philo;

//main.c
int	main(int ac, char **av);

//init.c
t_table *init_table(int ac, char **av);
t_philo	*init_philo(t_table *table);
int		init_mutex(t_table *table);
int		init_mutex_flag(t_table *table);

void	init_threads(t_table *table);
void	join_threads(t_table *table);

//utils.c
void	blocking_time(time_t ms, t_table *table);
time_t	get_ms_time();
void	safe_print(t_table *table, int id, const char *s, long time);
// t_state	get_philo_state(t_philo *philo);
// void	set_philo_state (t_philo *philo, t_state state);

//philo_single.c
void	*philo_single(void *data);

//thread_routine.c
void	*philo_routine(void *data);
void	think(t_philo *philo);
bool	try_take_forks(t_philo *philo);
void	putdown_forks(t_philo *philo);
void	eat(t_philo *philo);
void	philo_sleep(t_philo *philo);

//monitor.c
void	*monitor_routine(void *data);
bool	is_full(t_philo *philo);
bool	is_someone_dead(t_table *table);

//parsing.c
bool	is_valid(int ac, char **av);
int		ft_atoi(char *str);

//free.c
void	all_free(t_table *table);