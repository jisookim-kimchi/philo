/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokim2 <jisokim2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:17:34 by jisokim2          #+#    #+#             */
/*   Updated: 2025/06/28 15:17:37 by jisokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_single_thread(t_table *table)
{
	int	check;

	check = 0;
	if (!table)
		return (-1);
	if (table->philo_num == 1)
	{
		check = pthread_create(&table->philos[0].thread,
				NULL, philo_single, (void *)&table->philos[0]);
		if (check)
		{
			pthread_join(table->philos[0].thread, NULL);
			return (-1);
		}
		return (1);
	}
	return (0);
}

int	init_threads(t_table *table)
{
	int	i;
	int	result;

	i = 0;
	result = init_single_thread(table);
	if (result == -1)
		return (-1);
	else if (result == 1)
		return (1);
	while (i < table->philo_num)
	{
		if (i % 2 == 0)
			usleep(1000);
		result = pthread_create(&table->philos[i].thread, NULL,
				philo_routine, (void *)&table->philos[i]);
		if (result)
		{
			while (--i >= 0)
				pthread_join(table->philos[i].thread, NULL);
			return (-1);
		}
		i++;
	}
	return (1);
}
