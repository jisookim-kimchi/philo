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
			printf(RED" %lld im died\n"DEFAULT,get_ms_time() -table->start_time);
			break;
		}
		safe_print(table, philo->id, "think", get_ms_time() - table->start_time);
		usleep(200);
		if (!try_take_forks(philo))
		{
			usleep(500);
			continue;
		}
	}
	return (NULL);
}
