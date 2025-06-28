/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokim2 <jisokim2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:35:16 by jisokim2          #+#    #+#             */
/*   Updated: 2025/06/28 15:17:46 by jisokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	*init_table(int ac, char **av)
{
	t_table			*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->philo_num = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->must_eat_counts = ft_atoi(av[5]);
	else
		table->must_eat_counts = -1;
	table->someone_died = false;
	if (init_mutex_flag(table) == -1)
		return (NULL);
	return (table);
}

int	init_mutex_flag(t_table *table)
{
	int	i;

	i = 0;
	table->forks_mutex_flag = malloc(sizeof(bool) * table->philo_num);
	if (!table->forks_mutex_flag)
		return (-1);
	while (i < table->philo_num)
	{
		table->forks_mutex_flag[i] = false;
		i++;
	}
	table->print_mutex_flag = false;
	table->shut_down_mutex_flag = false;
	table->eat_mutex_flag = false;
	table->monitor_flag = false;
	table->monitor_flag = false;
	return (1);
}

static int	init_fork_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (1);
		else
			table->forks_mutex_flag[i] = true;
		i++;
	}
	return (0);
}

int	init_mutex(t_table *table)
{
	if (init_fork_mutex(table) != 0)
		return (-1);
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
		return (-1);
	else
		table->print_mutex_flag = true;
	if (pthread_mutex_init(&table->shutdown_mutex, NULL) != 0)
		return (-1);
	else
		table->shut_down_mutex_flag = true;
	if (pthread_mutex_init(&table->eat_mutex, NULL) != 0)
		return (-1);
	else
		table->eat_mutex_flag = true;
	if (pthread_mutex_init(&table->monitor, NULL) != 0)
		return (-1);
	else
		table->monitor_flag = true;
	return (1);
}

t_philo	*init_philo(t_table *table)
{
	int	num;
	int	i;

	i = 0;
	num = table->philo_num;
	table->philos = malloc(sizeof(t_philo) * num);
	table->forks = malloc(sizeof(pthread_mutex_t) * num);
	if (!table->philos || !table->forks)
		return (NULL);
	table->start_time = get_ms_time();
	while (i < num)
	{
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		table->philos[i].eat_counts = 0;
		table->philos[i].last_meal_time = table->start_time;
		table->philos[i].left_fork = i;
		table->philos[i].right_fork = (i + 1) % table->philo_num;
		i++;
	}
	return (table->philos);
}
