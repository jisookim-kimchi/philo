/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokim2 <jisokim2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:19:23 by jisokim2          #+#    #+#             */
/*   Updated: 2025/06/28 15:23:45 by jisokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//check fork delayd time
	// start_time = get_ms_time();
	// pthread_mutex_lock(&philo->table->forks[second]);
	// long long after_second = get_ms_time();
	// safe_print(philo, philo->id, 
	//"[DEBUG] second fork locked, delay", after_second - start_time);

void	set_fork_order(t_philo *philo, int *first, int *second)
{
	if (philo->left_fork < philo->right_fork)
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
}

bool	take_fork(t_philo *philo, int fork_idx, const char *msg)
{
	pthread_mutex_lock(&philo->table->forks[fork_idx]);
	if (is_someone_dead(philo))
	{
		putdown_onefork(&philo->table->forks[fork_idx]);
		return (false);
	}
	safe_print(philo, philo->id, msg, get_ms_time() - philo->table->start_time);
	return (true);
}

void	putdown_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
}

void	putdown_onefork(pthread_mutex_t *fork1)
{
	pthread_mutex_unlock(fork1);
}
