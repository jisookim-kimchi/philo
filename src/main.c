#include "philo.h"

/*
	arguments 
	number of philos, time_to_die, time_to_eat, time_to_sleep, must_eat_counts
*/

static void	error_print(t_table *table, const char *msg)
{
	if (!table)
	{
		printf(RED"%s\n"DEFAULT, msg);
	}
	all_free(table);
}

int	main(int ac, char **av)
{
	t_table	*table;

	if (!is_valid(ac, av))
	{
		printf(RED"INVALID ARGUMENTS\n"DEFAULT);
		return (-1);
	}
	table = init_table(ac, av);
	if (!table)
		return error_print(NULL, "TABLE INIT FAIL"), -1;
	if (!init_philo(table))
		return error_print(NULL, "PHILO INIT FAIL"), -1;
	if (init_mutex(table) == -1)
		return error_print(NULL, "MUTEX INIT FAIL"), -1;
	if (init_threads(table) == -1)
		return error_print(NULL, "THREAD INIT FAIL"), -1;
	join_threads(table);
	all_free(table);
	return (0);
}
