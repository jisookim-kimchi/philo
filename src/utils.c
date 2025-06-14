#include "philo.h"

// void	safe_print(t_table *table, int id, const char *s, long time)
// {
// 	pthread_mutex_lock(&table->print_mutex);
// 	if (!is_someone_dead(table))
// 	{
// 		printf("%ld %d %s\n", time, id, s);
// 	}
// 	pthread_mutex_unlock(&table->print_mutex);
// }

void	safe_print(t_philo *philo, int id, const char *s, long long time)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	if (!is_someone_dead(philo))
		printf("%lld %d %s\n", time, id, s);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

time_t	get_ms_time()
{
	struct timeval	tv;
	long long		ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
	/*
		1 -> 1000ms + to avoid of losing ms
	*/
}

//Accurate thread blocking for a given time
void	blocking_time(time_t ms, t_table *table)
{
	time_t	start;

	(void)table;
	start = get_ms_time();
	while (get_ms_time() - start < ms)
	{
		// if (is_someone_dead(table))
		// {
		//  	printf(RED"someone died\n"DEFAULT);
		//  	return;
		// }
		usleep(200);
	}
}

// void	set_philo_state (t_philo *philo, t_state state)
// {
// 	pthread_mutex_lock(&philo->state_mutex);
// 	philo->state = state;
// 	pthread_mutex_unlock(&philo->state_mutex);
// }

// t_state	get_philo_state(t_philo *philo)
// {
// 	t_state	state;

// 	pthread_mutex_lock(&philo->state_mutex);
// 	state = philo->state;
// 	pthread_mutex_unlock(&philo->state_mutex);
// 	return (state);
// }
