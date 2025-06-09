#include "philo.h"

// void	think(t_philo *philo)
// {
// 	t_table *table;

// 	table = philo->table;
// 	if (is_someone_dead(table))
// 	{
// 		safe_print(table, philo->id, RED"philo said someone died\n"DEFAULT,  get_ms_time() - table->start_time);
// 		return ;
// 	}
// 	safe_print(table, philo->id, YELLOW"is thinking"DEFAULT, get_ms_time() - table->start_time);
// }

bool	try_take_forks(t_philo *philo)
{
	int	left_fork_num = philo->id;
	int	right_fork_num;
	t_table *table = philo->table;

	left_fork_num = philo->id;
	right_fork_num = (philo->id) % philo->table->philo_num;

	if (is_someone_dead(table))
        return (false);
	if (philo->right_fork == philo->left_fork)
	{
		safe_print(table, philo->id, "has taken right fork", get_ms_time() - table->start_time);
		return false;
	}
	if (left_fork_num < right_fork_num)
	{
		pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
		if (is_someone_dead(table))
		{
			safe_print(table, philo->id, RED"philo said someone died"DEFAULT,  get_ms_time() - table->start_time);
			return putdown_onefork(&philo->table->forks[philo->left_fork]);
		}
		safe_print(table, philo->id, "has taken the left fork", get_ms_time() - table->start_time);
		pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
		if (is_someone_dead(table))
		{
			safe_print(table, philo->id, RED"philo said someone died"DEFAULT,  get_ms_time() - table->start_time);
			return putdown_onefork(&philo->table->forks[philo->right_fork]);
		}
		safe_print(table, philo->id, "has taken the right fork",  get_ms_time() - table->start_time);
	}
	else
	{
		pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
		if (is_someone_dead(table))
		{
			safe_print(table, philo->id, RED"philo said someone died"DEFAULT,  get_ms_time() - table->start_time);
			return putdown_onefork(&philo->table->forks[philo->right_fork]);
		}
		safe_print(table, philo->id, "has taken the right fork",  get_ms_time() - table->start_time);
		pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
		if (is_someone_dead(table))
		{
			safe_print(table, philo->id, RED"philo said someone died"DEFAULT,  get_ms_time() - table->start_time);
			return putdown_onefork(&philo->table->forks[philo->left_fork]);
		}
		safe_print(table, philo->id, "has taken the left fork", get_ms_time() - table->start_time);
	}
	return (true);
}

void	putdown_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
}

int	putdown_onefork(pthread_mutex_t *fork1)
{
	pthread_mutex_unlock(fork1);
	return 0;
}

void	eat(t_philo *philo)
{
	t_table *table;

	table = philo->table;
	if (is_someone_dead(table))
	{
		safe_print(table, philo->id, RED"philo said someone died"DEFAULT,  get_ms_time() - table->start_time);
		return;
	}
	pthread_mutex_lock(&table->eat_mutex);
	philo->last_meal_time = get_ms_time();
	philo->eat_counts++;
	pthread_mutex_unlock(&table->eat_mutex);
	safe_print(table, philo->id, GREEN"is eating"DEFAULT,  get_ms_time() - table->start_time);
	blocking_time(table->time_to_eat, table);
	
}

void	philo_sleep(t_philo *philo)
{
	t_table *table;

	table = philo->table;
	if (is_someone_dead(table))
	{
		safe_print(table, philo->id, RED"philo said someone died"DEFAULT,  get_ms_time() - table->start_time);
		return ;
	}
	safe_print(table, philo->id, BLUE"is sleeping"DEFAULT,  get_ms_time() - table->start_time);
	blocking_time(table->time_to_sleep, table);
}

void	*philo_routine(void *data)
{
	t_philo *philo = (t_philo *)data;
	t_table *table = philo->table;

	// if (philo->id % 2 == 0)
	// 	blocking_time(table->time_to_eat * 1, table);
	while (1)
	{
		if (!try_take_forks(philo))
		{
			//usleep(1000);
			continue;
		}
		eat(philo);
		if (is_full(philo))
		{
			putdown_forks(philo);
			safe_print(table, philo->id, RED"im full"DEFAULT,  get_ms_time() - table->start_time);
			break;
		}
		putdown_forks(philo);
		philo_sleep(philo);
		safe_print(table, philo->id, YELLOW"think"DEFAULT,  get_ms_time() - table->start_time);
	}
	return (NULL);
}

