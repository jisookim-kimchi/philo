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
	table->time_to_die = atoi(av[2]);
	table->time_to_eat = atoi(av[3]);
	table->time_to_sleep = atoi(av[4]);
	if (ac == 6)
		table->must_eat_counts = atoi(av[5]);
	else
		table->must_eat_counts = -1;
	while (i < table->philo_num)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	table->philos = init_philo(table);
	if (!table->philos)
		//handle error	
	return table;
}

t_philo	*init_philo(t_table *table)
{
	int	num;
	int	i;

	i = 0;
	num = table->philo_num;
	t_philo *philos = malloc(sizeof(t_philo) * num);
	if (!philos)
		//handle error
	while (i < num)
	{
		philos[i].id = i;
		philos[i].eat_counts = 0;
		philos[i].last_meal_time = 0;
		philos[i].left_fork = &table->forks[i];
		philos[i].right_fork = &table->forks[(i + 1) % num];
		philos[i].state = THINKING_READY;
		i++;
	}
	return philos;
}

void	init_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		//pthread_create(&table->philos[i].thread, NULL, routine, (void *)table->philos[i]);
		i++;
	}
}

void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		//pthread_join(&table->philos[i].thread, NULL, routine, (void *)table->philos[i]);
		i++;
	}
}