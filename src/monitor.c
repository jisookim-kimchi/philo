#include "philo.h"

bool	is_someone_dead(t_table *table)
{
	bool	check;

	check = false;
	pthread_mutex_lock(&table->shutdown_mutex);
	check = table->someone_died;
	pthread_mutex_unlock(&table->shutdown_mutex);
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
	//pthread_mutex_lock(&philo->meal_mutex);
	full = ((int)philo->eat_counts >= table->must_eat_counts);
	//pthread_mutex_unlock(&philo->meal_mutex);
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
		//pthread_mutex_lock(&table->philos[i].meal_mutex);
		if (table->philos[i].eat_counts >= table->must_eat_counts)
		{
			stuffed_cnts++;
		}
		//pthread_mutex_unlock(&table->philos[i].meal_mutex);
		i++;
	}
	return (stuffed_cnts);
}

void	*monitor_routine(void *data)
{
	t_table *table;
	time_t time_to_die;
	int	i;
	int	cnts;

	cnts = 0;
	table = (t_table *) data;
	time_to_die = table->time_to_die;
	while (1)
	{
		i = 0;
		while(i < table->philo_num)
		{
			//pthread_mutex_lock(&table->philos[i].meal_mutex);
			time_t last_meal = table->philos[i].last_meal_time;
			//pthread_mutex_unlock(&table->philos[i].meal_mutex);
			if (get_ms_time() - last_meal >= time_to_die)
			{
				safe_print(table, table->philos[i].id + 1, RED"monitor said : died\n"DEFAULT, get_ms_time()- table->start_time);
				pthread_mutex_lock(&table->shutdown_mutex);
				table->someone_died = true;
				pthread_mutex_unlock(&table->shutdown_mutex);
				return NULL;
			}
			i++;
		}
		cnts = check_stuffed_cnts(table);
		if (cnts == table->philo_num)
		{
			break;
		}
		usleep(1000);
	}
	return (NULL);
}
