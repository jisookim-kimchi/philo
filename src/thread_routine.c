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
	if (is_someone_dead(table))
	{
		printf(RED" philo said who died\n"DEFAULT);
		return ;
	}
	set_philo_state(philo, THINKING_READY);
	pthread_mutex_lock(&table->print_mutex);
	printf(YELLOW"%ld %d is thinking\n"DEFAULT, get_ms_time() - table->start_time, philo->id); 
	pthread_mutex_unlock(&table->print_mutex);
}

bool	try_take_forks(t_philo *philo)
{
	int	left_fork_num = philo->id;
	int	right_fork_num;
	t_table *table = philo->table;

	left_fork_num = philo->id;
	right_fork_num = (philo->id + 1) % philo->table->philo_num;

	if (is_someone_dead(table))
        return (false);
	if (left_fork_num < right_fork_num)
	{
		pthread_mutex_lock(philo->left_fork);
		printf("%ld %d has taken left fork\n", get_ms_time()- philo->table->start_time, philo->id);
		if (is_someone_dead(table))
		{
			pthread_mutex_unlock(philo->left_fork);
			return (false);
		}
		pthread_mutex_lock(philo->right_fork);
		if (is_someone_dead(table))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (false);
		}
		printf(YELLOW"%ld %d has taken right fork\n"DEFAULT, get_ms_time()- philo->table->start_time, philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		printf("%ld %d has taken right fork\n", get_ms_time()- philo->table->start_time, philo->id);
		if (is_someone_dead(table))
		{
			pthread_mutex_unlock(philo->right_fork);
			return (false);
		}
		pthread_mutex_lock(philo->left_fork);
		if (is_someone_dead(table))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (false);
		}
		printf("%ld %d has taken left fork\n", get_ms_time()- philo->table->start_time, philo->id);
	}
	return (true);
}

void	putdown_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	eat(t_philo *philo)
{
	t_table *table;

	table = philo->table;
	if (is_someone_dead(table))
		return;
	set_philo_state(philo, EATING_RUNNING);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_ms_time();
	philo->eat_counts++;
	pthread_mutex_unlock(&philo->meal_mutex);

	printf(GREEN"%ld %d is eating\n"DEFAULT, get_ms_time() - table->start_time, philo->id);
	blocking_time(table->time_to_eat, table);
}

void	philo_sleep(t_philo *philo)
{
	t_table *table;

	table = philo->table;
	if (is_someone_dead(table))
	{
		printf(RED" philo said who died\n"DEFAULT);
		return ;
	}
	set_philo_state(philo, SLEEPING_BLOCKED);
	pthread_mutex_lock(&table->print_mutex);
	printf(BLUE"%ld %d is sleeping\n"DEFAULT, get_ms_time() - table->start_time, philo->id);
	pthread_mutex_unlock(&table->print_mutex);
	blocking_time(table->time_to_sleep, table);
}

void	*philo_routine(void *data)
{
	t_philo *philo = (t_philo *)data;
	t_table *table = philo->table;

	while (!is_someone_dead(table) && !is_full(philo))
	{
		if (!try_take_forks(philo))
			break;
		eat(philo);
		if (is_full(philo))
		{
			putdown_forks(philo);
			printf(RED"im full\n"DEFAULT);
			break;
		}
		putdown_forks(philo);
		philo_sleep(philo);
		think(philo);
	}
	return (NULL);
}

