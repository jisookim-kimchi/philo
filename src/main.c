#include "philo.h"

/*
	arguments 
	number of philos, time_to_die, time_to_eat, time_to_sleep, must_eat_counts
*/

int	main(int ac, char **av)
{
	t_table	*table;
	unsigned int i;

	i = 0;
	if (ac != 5 && ac != 6)
		return (-1);
	table = init_table(ac, av);
	table->start_time = get_ms_time();
	while (i < table->philo_num)
	{
		table->philos[i].last_meal_time = table->start_time;
		i++;
	}
	pthread_create(&table->monitor, NULL, monitor_routine, (void *)table);
	init_threads(table);
	join_threads(table);
	pthread_join(table->monitor, NULL);
	
	return (0);
}
