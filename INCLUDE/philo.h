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

typedef enum e_state
{
	DIED_TERMINATE = 0,
	EATING_RUNNING,
	SLEEPING_BLOCKED,
	THINKING_READY,
}	e_state;

typedef struct s_table
{
	unsigned int	philo_num;
	time_t			time_to_die;
	time_t			time_to_sleep;
	time_t			time_to_eat;
	time_t			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	state_mutex;

	unsigned int	must_eat_counts;
	bool			someone_died;
	struct s_philo	*philos;
	pthread_t		monitor; 
}	t_table;

typedef struct s_philo
{
	pthread_t		thread;
	time_t			last_meal_time;
	unsigned int	id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	unsigned int	eat_counts;
	e_state			state;
	t_table			*table;
}	t_philo;

//main.c
int	main(int ac, char **av);

//init.c
t_table *init_table(int ac, char **av);
t_philo	*init_philo(t_table *table);
void	init_threads(t_table *table);
void	join_threads(t_table *table);

//utils.c
void	blocking_time(time_t ms);
time_t	get_ms_time();

//thread_routine.c
void	*philo_routine(void *arg);
void	think(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	eat(t_philo *philo);

//monitor.c
void	*monitor_routine(void *arg);