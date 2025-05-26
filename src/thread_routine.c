#include "philo.h"

void	think(t_philo *philo)
{
	t_table *table;
	time_t	time_to_think;

	// table = philo->table;
	// pthread_mutex_lock(&table->state_mutex);
	// philo->state = THINKING_READY;
	// phtread_mutex_unlock(&table->state_mutex);

	time_to_think = table->time_to_die - (table->time_to_eat + table->time_to_sleep);
	if (time_to_think < 0)
		time_to_think = 0;
	blocking_time(time_to_think);

	pthread_mutex_lock(&table->state_mutex);
	philo->state = EATING_RUNNING;
	phtread_mutex_unlock(&table->state_mutex);
}

void	eat(t_philo *philo)
{
	t_table *table;
	table = philo->table;

	if (philo->id %2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	philo->last_meal_time = get_ms_time();
	pthread_mutex_lock(&table->print_mutex);
	printf("philo %d eating\n", philo->id);
	pthread_mutex_unlock(&table->print_mutex);
	blocking_time(table->time_to_eat);
	
	pthread_mutex_lock(&table->state_mutex);
	philo->state = SLEEPING_BLOCKED;
	pthread_mutex_unlock(&table->state_mutex);
}

void	sleep_philo(t_philo *philo)
{
	t_table *table;

	table = philo->table;
	pthread_mutex_lock(&table->print_mutex);
	printf("%d is sleeping\n", philo->id);
	pthread_mutex_unlock(&table->print_mutex);

	blocking_time(table->time_to_sleep);
	pthread_mutex_lock(&table->state_mutex);
	philo->state = THINKING_READY;
	pthread_mutex_unlock(&table->state_mutex);
}

void	*routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_table *table = philo->table;

	while (1)
	{
		pthread_mutex_lock(&table->state_mutex);
		int died = table->someone_died;
		pthread_mutex_unlock(&table->state_mutex);

		if (philo->state == THINKING_READY)
		{
			if (died)
				break;
			think(philo);
		}
		else if (philo->state == EATING_RUNNING)
		{
			if (died)
				break;
			eat(philo);
		}
		else if (philo->state == SLEEPING_BLOCKED)
		{
			if (died)
				break;
			sleep(philo);
		}
		//allfree!
		//thread_died();
	}
	return (NULL);
}