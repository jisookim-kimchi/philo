/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_single.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokim2 <jisokim2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:35:40 by jisokim2          #+#    #+#             */
/*   Updated: 2025/06/22 14:46:36 by jisokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_single(void *data)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *) data;
	table = philo->table;
	while (1)
	{
		if (is_someone_dead(philo))
		{
			printf(RED"%lld im died\n"DEFAULT,
				get_ms_time() - table->start_time);
			break ;
		}
		safe_print(philo, philo->id, "think",
			get_ms_time() - table->start_time);
		usleep(200);
		if (!try_take_forks(philo))
		{
			usleep(500);
			continue ;
		}
	}
	return (NULL);
}
