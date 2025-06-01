#include "philo.h"

void	think(t_philo *philo)
{
	t_table *table;

	table = philo->table;
	if (is_someone_dead(table))
	{
		printf(RED"someone died\n"DEFAULT);
		return ;
	}
	set_philo_state(philo, THINKING_READY);
	safe_print(table, philo->id, YELLOW"is thinking"DEFAULT, get_ms_time() - table->start_time);
	blocking_time(table->time_to_die - (table->time_to_eat + table->time_to_sleep), table);
}

bool	try_take_forks(t_philo *philo)
{
	int	left_fork_num = philo->id;
	int	right_fork_num;
	t_table *table = philo->table;

	left_fork_num = philo->id;
	right_fork_num = (philo->id + 1) % philo->table->philo_num;

	if (is_someone_dead(table))
	{
		printf(RED"someone died\n"DEFAULT);
        return (false);
	}
	if (left_fork_num < right_fork_num)
	{
		pthread_mutex_lock(philo->left_fork);
		if (is_someone_dead(table))
		{
			printf(RED"someone died\n"DEFAULT);
			pthread_mutex_unlock(philo->left_fork);
			return (false);
		}
		safe_print(table, philo->id, "has taken the left fork",  get_ms_time() - table->start_time);
		pthread_mutex_lock(philo->right_fork);
		if (is_someone_dead(table))
		{
			printf(RED"someone died\n"DEFAULT);
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (false);
		}
		safe_print(table, philo->id, "has taken the right fork",  get_ms_time() - table->start_time);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		if (is_someone_dead(table))
		{
			printf(RED"someone died\n"DEFAULT);
			pthread_mutex_unlock(philo->right_fork);
			return (false);
		}
		safe_print(table, philo->id, "has taken the right fork",  get_ms_time() - table->start_time);
		pthread_mutex_lock(philo->left_fork);
		if (is_someone_dead(table))
		{
			printf(RED"someone died\n"DEFAULT);
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (false);
		}
		safe_print(table, philo->id, "has taken the left fork", get_ms_time() - table->start_time);
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
	{
		printf(RED"someone died\n"DEFAULT);
		return;
	}
	set_philo_state(philo, EATING_RUNNING);

	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_ms_time();
	printf("philos : %p\n", philo);
	philo->eat_counts++;
	pthread_mutex_unlock(&philo->meal_mutex);
	safe_print(table, philo->id, GREEN"is eating"DEFAULT,  get_ms_time() - table->start_time);
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
	safe_print(table, philo->id, BLUE"is sleeping"DEFAULT,  get_ms_time() - table->start_time);
	blocking_time(table->time_to_sleep, table);
}

void	*philo_routine(void *data)
{
	t_philo *philo = (t_philo *)data;
	t_table *table = philo->table;

	while (!is_someone_dead(table) && !is_full(philo))
	{
		if (!try_take_forks(philo))
		{
			continue;
		}
		eat(philo);
		if (is_full(philo))
		{
			putdown_forks(philo);
			safe_print(table, philo->id, RED"im full\n"DEFAULT,  get_ms_time() - table->start_time);
			break;
		}
		putdown_forks(philo);
		philo_sleep(philo);
		think(philo);
	}
	return (NULL);
}

