#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_table *table;
	time_t time_to_die;
	unsigned int	i;

	table = (t_table *) arg;
	time_to_die = table->time_to_die;
	while (1)
	{
		i = 0;
		while(i < table->philo_num)
		{
			pthread_mutex_lock(&table->state_mutex);
			if (get_ms_time() - table->philos[i].last_meal_time > time_to_die)
			{
				pthread_mutex_lock(&table->state_mutex);
				table->philos[i].state = DIED_TERMINATE;
				table->someone_died = true;
				pthread_mutex_unlock(&table->state_mutex);
				//okay
				pthread_mutex_lock(&table->print_mutex);
				printf(RED" %ld, time to die : %ld %d is died\n"DEFAULT, get_ms_time() - table->philos[i].last_meal_time, time_to_die, table->philos[i].id);
				pthread_mutex_unlock(&table->print_mutex);
				return NULL;
			}
			pthread_mutex_unlock(&table->state_mutex);
			i++;
		}
		usleep(100);
	}
	return (NULL);
}
