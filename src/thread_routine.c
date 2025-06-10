#include "philo.h"

//check fork delayd time
	// start_time = get_ms_time();
	// pthread_mutex_lock(&philo->table->forks[second]);
	// long long after_second = get_ms_time();
	// safe_print(philo, philo->id, "[DEBUG] second fork locked, delay", after_second - start_time);

bool	try_take_forks(t_philo *philo)
{
	t_table *table = philo->table;
	int	first;
	int	second;
	if (should_stop(philo))
        return (false);
	if (philo->right_fork == philo->left_fork)
	{
		safe_print(philo, philo->id, "has taken right fork", get_ms_time() - table->start_time);
		return false;
	}
	if (philo->left_fork < philo->right_fork)
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	else
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	pthread_mutex_lock(&table->forks[first]);
	
	if (is_someone_dead(philo))
	{
		putdown_onefork(&philo->table->forks[first]);
		return false;
	}
	safe_print(philo, philo->id, "has taken first fork", get_ms_time() - table->start_time);
	pthread_mutex_lock(&table->forks[second]);
	
	if (is_someone_dead(philo))
	{
		putdown_forks(philo);
		return false;
	}
	safe_print(philo, philo->id, "has taken second fork", get_ms_time() - table->start_time);
	return (true);
}

void	putdown_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
}

void	putdown_onefork(pthread_mutex_t *fork1)
{
	pthread_mutex_unlock(fork1);
}

void	eat(t_philo *philo)
{
	t_table *table;

	table = philo->table;

	pthread_mutex_lock(&table->eat_mutex);
	philo->last_meal_time = get_ms_time();
	philo->eat_counts++;
	pthread_mutex_unlock(&table->eat_mutex);
	safe_print(philo, philo->id, GREEN"is eating"DEFAULT,  get_ms_time() - table->start_time);
	blocking_time(table->time_to_eat, philo);
}

void	philo_sleep(t_philo *philo)
{
	t_table *table;

	table = philo->table;
	if (is_someone_dead(philo))
	{
		return ;
	}
	safe_print(philo, philo->id, BLUE"is sleeping"DEFAULT,  get_ms_time() - table->start_time);
	blocking_time(table->time_to_sleep, philo);
}

void	*philo_routine(void *data)
{
	t_philo *philo = (t_philo *)data;
	t_table *table = philo->table;

	if (philo->id % 2 == 1)
		blocking_time(table->time_to_eat * 1, philo);
	while (1)
	{
		if (is_someone_dead(philo))
        	break;
		if (!try_take_forks(philo))
		{
			continue;
		}
		if (is_someone_dead(philo))
		{
			putdown_forks(philo);
			break;
		}
		eat(philo);
		if (is_full(philo))
		{
			putdown_forks(philo);
			break;
		}
		putdown_forks(philo);
		philo_sleep(philo);
		if (!should_stop(philo))
			safe_print(philo, philo->id, YELLOW"think"DEFAULT,  get_ms_time() - table->start_time);
	}
	return (NULL);
}

