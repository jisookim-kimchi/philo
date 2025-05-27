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

	//pthread_mutex_lock(&table->state_mutex);
	philo->state = EATING_RUNNING;
	//pthread_mutex_unlock(&table->state_mutex);
}

void	eat(t_philo *philo)
{
	t_table *table;

	table = philo->table;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		printf(ORANGE"%ld %d has taken forks\n"DEFAULT, get_ms_time() - table->start_time, philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
		printf(ORANGE"%ld %d has taken forks\n"DEFAULT, get_ms_time() - table->start_time, philo->id);
	}
	pthread_mutex_lock(&table->print_mutex);
	pthread_mutex_unlock(&table->print_mutex);
	pthread_mutex_lock(&table->state_mutex);
	philo->last_meal_time = get_ms_time();
	pthread_mutex_unlock(&table->state_mutex);

	pthread_mutex_lock(&table->print_mutex);
	printf(GREEN"%ld %d is eating\n"DEFAULT, get_ms_time() - table->start_time, philo->id);
	blocking_time(table->time_to_eat);
	pthread_mutex_unlock(&table->print_mutex);
	philo->eat_counts++;
	
	//fork put down
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);

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
	t_table *table = philo->table;

	while (1)
	{
		pthread_mutex_lock(&table->state_mutex);
        if (table->someone_died)
        {
            pthread_mutex_unlock(&table->state_mutex);
            break;  // 안전하게 종료
        }
        pthread_mutex_unlock(&table->state_mutex);
		if (philo->state == THINKING_READY)
		{
			think(philo);
		}
		else if (philo->state == EATING_RUNNING)
		{
			eat(philo);
		}
		else if (philo->state == SLEEPING_BLOCKED)
		{
			philo_sleep(philo);
		}
		//allfree!
		//thread_died();
	}
	return (NULL);
}