#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>
#include <pthread.h>

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
	bool			someone_died;
	struct s_philo	*philos;
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

