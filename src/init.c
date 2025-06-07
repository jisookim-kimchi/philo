# include "philo.h"

t_table *init_table(int ac, char **av)
{
	t_table			*table;
	int	i;

	i = 0;
	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->philo_num = ft_atoi(av[1]);
	table->forks_mutex_flag = malloc(sizeof(bool) * table->philo_num);
	if (!table->forks_mutex_flag)
		return (NULL);
	table->print_mutex_flag = false;
	table->someone_died_mutex_flag = false;
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
	{
		table->print_mutex_flag = false;
		return (NULL);
	}
	else
		table->print_mutex_flag = true;
	if (pthread_mutex_init(&table->someone_died_mutex, NULL) != 0)
	{
		table->someone_died_mutex_flag = false;
		return (NULL);
	}
	else
		table->someone_died_mutex_flag = true;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_num);
	if (!table->forks)
		return (NULL);
	while (i < table->philo_num)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			table->forks_mutex_flag[i] = false;
			return (NULL);
		}
		else
			table->forks_mutex_flag[i] = true; 
		i++;
	}
	table->someone_died = false;
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->must_eat_counts = ft_atoi(av[5]);
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
		philos[i].last_meal_time = 0;
		if (pthread_mutex_init(&philos[i].meal_mutex, NULL) != 0)
		{
			philos[i].meal_mutex_flag = false;
			return (NULL);
		}
		else
			philos[i].meal_mutex_flag = true;
		if (pthread_mutex_init(&philos[i].state_mutex, NULL) != 0)
		{
			philos[i].state_mutex_flag = false;
			return (NULL);
		}
		else
			philos[i].state_mutex_flag = true;
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
	int	result;

	i = 0;
	while (i < table->philo_num)
	{
		result = pthread_create(&table->philos[i].thread, NULL, philo_routine, (void *)&table->philos[i]);
		if (result)
		{
			while (--i >= 0)
			{
				pthread_join(table->philos[i].thread, NULL);
			}
			break;
		}
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