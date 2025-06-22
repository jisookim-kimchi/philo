/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokim2 <jisokim2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:35:09 by jisokim2          #+#    #+#             */
/*   Updated: 2025/06/22 14:38:56 by jisokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	mutex_flag_free(t_table *table)
{
	if (!table)
		return ;
	if (table->forks_mutex_flag)
		free(table->forks_mutex_flag);
	if (table->shut_down_mutex_flag)
		pthread_mutex_destroy(&table->shutdown_mutex);
	if (table->print_mutex_flag)
		pthread_mutex_destroy(&table->print_mutex);
	if (table->monitor_flag)
		pthread_mutex_destroy(&table->monitor);
	if (table->eat_mutex_flag)
		pthread_mutex_destroy(&table->eat_mutex);
}

void	all_free(t_table *table)
{
	int	i;

	i = 0;
	if (!table)
		return ;
	if (table->philos)
		free(table->philos);
	if (table->forks)
	{
		i = 0;
		while (i < table->philo_num)
		{
			if (table->forks_mutex_flag[i])
				pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
		free(table->forks);
	}
	mutex_flag_free(table);
	free(table);
}
