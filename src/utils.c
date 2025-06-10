#include "philo.h"

int		ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		i++;
	}
	return (i);
}

void	write_longlong(long long data)
{
	char c;
	if (data >= 10)
	{
		write_longlong(data / 10);
	}
	c = data % 10 + '0';
	write(1, &c, 1);
}

void	safe_print(t_philo *philo, int id, const char *str, long long time)
{
	// pthread_mutex_lock(&philo->table->shutdown_mutex);
	// if (philo->table->someone_died)
	// {
	// 	pthread_mutex_unlock(&philo->table->shutdown_mutex);
	// 	return;
	// }
	// pthread_mutex_unlock(&philo->table->shutdown_mutex);

	pthread_mutex_lock(&philo->table->print_mutex);
	write_longlong(time);
	write(1, " ", 1);
	write_longlong(id);
	write(1, " ", 1);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

//printf is internally thread-safe (protected between threads) but not fast
// void	safe_print(t_philo *philo, int id, const char *s, long long time)
// {
// 	//pthread_mutex_lock(&philo->table->print_mutex);
// 	(void)philo;
// 	printf("%lld %d %s\n", time, id, s);
// 	//pthread_mutex_unlock(&philo->table->print_mutex);
// }

long long	get_ms_time()
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
void	blocking_time(time_t ms, t_philo *philo)
{
	time_t	start;

	start = get_ms_time();
	while (get_ms_time() - start < ms)
	{
		if (is_someone_dead(philo))
		{
		 	return;
		}
		usleep(200);
	}
}
