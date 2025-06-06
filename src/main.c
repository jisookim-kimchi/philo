#include "philo.h"

/*
	arguments 
	number of philos, time_to_die, time_to_eat, time_to_sleep, must_eat_counts
*/

int	main(int ac, char **av)
{
	t_table	*table;
	int i;

	i = 0;
	if (!is_valid(ac, av))
	{
		printf(RED"INVALID ARGUMENTS\n"DEFAULT);
		return (-1);
	}
	table = init_table(ac, av);
	if (!table)
	{
		all_free(table);
		return (-1);
	}
	table->start_time = get_ms_time();
	while (i < table->philo_num)
	{
		table->philos[i].last_meal_time = table->start_time;
		i++;
	}
	pthread_create(&table->monitor, NULL, monitor_routine, (void *)table);
	init_threads(table);
	pthread_join(table->monitor, NULL);
	join_threads(table);
	all_free(table);
	return (0);
}
