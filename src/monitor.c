#include "philo.h"

bool	is_someone_dead(t_philo *philo)
{
	bool	check;
	t_table *table;

	table = philo->table;
	check = false;
	if (get_ms_time() - philo->last_meal_time >= table->time_to_die)
	{
		pthread_mutex_lock(&table->shutdown_mutex);
		check = table->someone_died;
		safe_print(philo, philo->id, "died\n", get_ms_time()-table->start_time);
		pthread_mutex_unlock(&table->shutdown_mutex);
	}
	return (check);
}

bool	is_full(t_philo *philo)
{
	t_table	*table;
	bool	full;

	full = false;
	table = philo->table;
	if (table->must_eat_counts == -1)
		return (full);
	pthread_mutex_lock(&table->eat_mutex);
	full = ((int)philo->eat_counts >= table->must_eat_counts);
	pthread_mutex_unlock(&table->eat_mutex);
	return full;
}

int	check_stuffed_cnts(t_table *table)
{
	int	i;
	int	stuffed_cnts;

	stuffed_cnts = 0;
	i = 0;

	if (table->must_eat_counts == -1)
		return (0);
	while (i < table->philo_num)
	{
		pthread_mutex_lock(&table->eat_mutex);
		if (table->philos[i].eat_counts >= table->must_eat_counts)
		{
			stuffed_cnts++;
		}
		pthread_mutex_unlock(&table->eat_mutex);
		i++;
	}
	return (stuffed_cnts);
}

int	should_stop(t_philo *philo)
{
	if (is_someone_dead(philo) == true)
		return 1;
	else if (is_full(philo) == true)
		return 1;
	else if (check_stuffed_cnts(philo->table))
		return 1;
	return 0;
}