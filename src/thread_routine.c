#include "philo.h"

void	think(t_philo *philo)
{
	t_table *table;
	time_t	time_to_think;

	table = philo->table;
	time_to_think = table->time_to_die - (table->time_to_eat + table->time_to_sleep);
	if (time_to_think < 0)
		time_to_think = 0;
	pthread_mutex_lock(&table->print_mutex);
	printf(YELLOW"%ld %d is thinking\n"DEFAULT, get_ms_time() - table->start_time, philo->id); 
	pthread_mutex_unlock(&table->print_mutex);
	blocking_time(time_to_think);

	//issue
	//pthread_mutex_lock(&table->state_mutex);
	//philo->state = EATING_RUNNING;
	//pthread_mutex_unlock(&table->state_mutex);
}

void	try_take_forks(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	pthread_mutex_lock(&table->print_mutex);
	printf(ORANGE"%ld %d has taken forks\n"DEFAULT, get_ms_time() - table->start_time, philo->id);
	pthread_mutex_unlock(&table->print_mutex);
}

void	putdown_fokrs(t_philo *philo)
{
	//fork put down
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	eat(t_philo *philo)
{
	t_table *table;

	table = philo->table;
	
	pthread_mutex_lock(&table->state_mutex);
	philo->last_meal_time = get_ms_time();
	pthread_mutex_unlock(&table->state_mutex);

	pthread_mutex_lock(&table->print_mutex);
	printf(GREEN"%ld %d is eating\n"DEFAULT, get_ms_time() - table->start_time, philo->id);
	pthread_mutex_unlock(&table->print_mutex);
	blocking_time(table->time_to_eat);
	philo->eat_counts++;
	//pthread_mutex_lock(&table->state_mutex);
	philo->state = SLEEPING_BLOCKED;
	//pthread_mutex_unlock(&table->state_mutex);
}

void	philo_sleep(t_philo *philo)
{
	t_table *table;

	table = philo->table;
	pthread_mutex_lock(&table->print_mutex);
	printf(BLUE"%ld %d is sleeping\n"DEFAULT, get_ms_time() - table->start_time, philo->id);
	pthread_mutex_unlock(&table->print_mutex);
	blocking_time(table->time_to_sleep);

	//pthread_mutex_lock(&table->state_mutex);
	philo->state = THINKING_READY;
	//pthread_mutex_unlock(&table->state_mutex);
}

void	*philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	while (1)
	{
		/*
			set_state (think);
			try_take_forks(philo);
			set_state(eating);
			eat();
			putdown_forks(philo);
			set_state(sleeping);
			sleep(philo);
		*/
		philo->state = THINKING_READY;
		try_take_forks(philo);
		philo->state = EATING_RUNNING;
		eat(philo);
		putdown_fokrs(philo);
		philo->state = SLEEPING_BLOCKED;
		philo_sleep(philo);
		think(philo);
	}
	return (NULL);
}

// eating -> sleep

// wakeup(sleep) -> think