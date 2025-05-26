# include "philo.h"

t_table *init_table(int ac, char **av)
{
	t_table *table;
	int		i;

	i = 0;
	table = malloc(sizeof(t_table));
	table->philo_num = atoi(av[1]);
	if (pthread_mutex_init(&table->state_mutex, NULL) != 0)
		//handle error
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
		//handle error
	table->someone_died = false;
	table->start_time = 0;
	
}