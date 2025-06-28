/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokim2 <jisokim2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:35:44 by jisokim2          #+#    #+#             */
/*   Updated: 2025/06/28 15:23:20 by jisokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	try_take_forks(t_philo *philo)
{
	t_table	*table;
	int		first;
	int		second;

	table = philo->table;
	first = 0;
	second = 0;
	if (should_stop(philo))
		return (false);
	if (philo->right_fork == philo->left_fork)
	{
		safe_print(philo, philo->id, "has taken first fork",
			get_ms_time() - table->start_time);
		return (false);
	}
	set_fork_order(philo, &first, &second);
	if (take_fork(philo, first, "has taken first fork") == false)
		return (false);
	if (take_fork(philo, second, "has taken second fork") == false)
	{
		putdown_onefork(&philo->table->forks[first]);
		return (false);
	}
	return (true);
}

void	eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->eat_mutex);
	philo->last_meal_time = get_ms_time();
	philo->eat_counts++;
	pthread_mutex_unlock(&table->eat_mutex);
	safe_print(philo, philo->id, GREEN"is eating"DEFAULT,
		get_ms_time() - table->start_time);
	blocking_time(table->time_to_eat, philo);
}

void	philo_sleep(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (is_someone_dead(philo))
	{
		return ;
	}
	safe_print(philo, philo->id, BLUE"is sleeping"DEFAULT,
		get_ms_time() - table->start_time);
	blocking_time(table->time_to_sleep, philo);
}

void	*philo_routine(void *data)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)data;
	table = philo->table;
	if (philo->id % 2 == 1)
		blocking_time(table->time_to_eat * 1, philo);
	while (!is_someone_dead(philo) && !is_full(philo))
	{
		if (!try_take_forks(philo))
			continue ;
		eat(philo);
		if (is_full(philo))
		{
			putdown_forks(philo);
			break ;
		}
		putdown_forks(philo);
		philo_sleep(philo);
		if (!should_stop(philo))
			safe_print(philo, philo->id, YELLOW"think"DEFAULT,
				get_ms_time() - table->start_time);
	}
	return (NULL);
}
