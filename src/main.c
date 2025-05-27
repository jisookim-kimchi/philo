#include "philo.h"

/*
	arguments 
	number of philos, time_to_die, time_to_eat, time_to_sleep, must_eat_counts
*/

int	main(int ac, char **av)
{
	t_table	*table;

	if (ac != 5 && ac != 6)
		return (-1);
	table = init_table(ac, av);
	init_threads(table);
	join_threads(table);
	
	
	return (0);
}
