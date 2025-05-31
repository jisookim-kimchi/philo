# include "philo.h"

t_table *init_table(int ac, char **av)
{
	t_table			*table;
	int	i;

	i = 0;
	table = malloc(sizeof(t_table));
	table->philo_num = atoi(av[1]);
	if (pthread_mutex_init(&table->state_mutex, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&table->someone_died_mutex, NULL) != 0)
		return (NULL);
	table->someone_died = false;
	table->start_time = get_ms_time();
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_num);
	if (!table->forks)
		return (NULL);
	while (i < table->philo_num)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	table->time_to_die = atoi(av[2]);
	table->time_to_eat = atoi(av[3]);
	table->time_to_sleep = atoi(av[4]);
	if (ac == 6)
		table->must_eat_counts = atoi(av[5]);
	else
		table->must_eat_counts = -1;
	table->philos = init_philo(table);
	if (!table->philos)
		return (NULL);
	return (table);
}

t_philo	*init_philo(t_table *table)
{
	int	num;
	int	i;

	i = 0;
	num = table->philo_num;
	t_philo *philos = malloc(sizeof(t_philo) * num);
	if (!philos)
		return (NULL);
	while (i < num)
	{
		philos[i].id = i;
		philos[i].table = table;
		philos[i].eat_counts = 0;
		if (pthread_mutex_init(&philos[i].meal_mutex, NULL) != 0)
			return (NULL);
		if (pthread_mutex_init(&philos[i].state_mutex, NULL) != 0)
			return (NULL);
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
		pthread_create(&table->philos[i].thread, NULL, philo_routine, (void *)&table->philos[i]);
		i++;
	}
}

void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
}