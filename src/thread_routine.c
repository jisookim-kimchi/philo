#include "philo.h"

void	set_philo_state (t_philo *philo, t_state state)
{
	pthread_mutex_lock(&philo->state_mutex);
	philo->state = state;
	pthread_mutex_unlock(&philo->state_mutex);
}

t_state	get_philo_state(t_philo *philo)
{
	t_state	state;

	pthread_mutex_lock(&philo->state_mutex);
	state = philo->state;
	pthread_mutex_unlock(&philo->state_mutex);
	return (state);
}
void	think(t_philo *philo)
{
	t_table *table;

	table = philo->table;
	set_philo_state(philo, THINKING_READY);
	pthread_mutex_lock(&table->print_mutex);
	printf(YELLOW"%ld %d is thinking\n"DEFAULT, get_ms_time() - table->start_time, philo->id); 
	pthread_mutex_unlock(&table->print_mutex);
}

void	try_take_forks(t_philo *philo)
{
	int	left_fork_num = philo->id;
	int	right_fork_num;

	left_fork_num = philo->id;
	right_fork_num = (philo->id + 1) % philo->table->philo_num;

	if (left_fork_num < right_fork_num)
	{
		pthread_mutex_lock(philo->left_fork);
		printf("%ld %d has taken left fork\n", get_ms_time()- philo->table->start_time, philo->id);
		pthread_mutex_lock(philo->right_fork);
		printf("%ld %d has taken right fork\n", get_ms_time()- philo->table->start_time, philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		printf("%ld %d has taken right fork\n", get_ms_time()- philo->table->start_time, philo->id);
		pthread_mutex_lock(philo->left_fork);
		printf("%ld %d has taken left fork\n", get_ms_time()- philo->table->start_time, philo->id);
	}
}

void	putdown_fokrs(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	eat(t_philo *philo)
{
	t_table *table;

	table = philo->table;
	set_philo_state(philo, EATING_RUNNING);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_ms_time();
	philo->eat_counts++;
	pthread_mutex_unlock(&philo->meal_mutex);

	printf(GREEN"%ld %d is eating\n"DEFAULT, get_ms_time() - table->start_time, philo->id);
	blocking_time(table->time_to_eat);
}

void	philo_sleep(t_philo *philo)
{
	t_table *table;

	table = philo->table;
	set_philo_state(philo, SLEEPING_BLOCKED);
	pthread_mutex_lock(&table->print_mutex);
	printf(BLUE"%ld %d is sleeping\n"DEFAULT, get_ms_time() - table->start_time, philo->id);
	pthread_mutex_unlock(&table->print_mutex);
	blocking_time(table->time_to_sleep);
}

void	*philo_routine(void *data)
{
	t_philo *philo = (t_philo *)data;

	while (1)
	{
		try_take_forks(philo);
		eat(philo);
		putdown_fokrs(philo);
		philo_sleep(philo);
		think(philo);
	}
	return (NULL);
}

