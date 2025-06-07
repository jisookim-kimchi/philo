#include "philo.h"

void	*philo_single(void *data)
{
	t_philo	*philo;
	t_table *table;

	philo = (t_philo *) data;
	table = philo->table;
	while (1)
	{
		if (is_someone_dead(table))
		{
			printf(RED" %ld im died\n"DEFAULT,get_ms_time() -table->start_time);
			break;
		}
		think(philo);
		usleep(200);
		if (!try_take_forks(philo))
		{
			usleep(500);
			continue;
		}
		eat(philo);
		putdown_forks(philo);
		philo_sleep(philo);
	}
	return (NULL);
}
