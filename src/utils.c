#include "philo.h"

time_t	get_ms_time()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
	/*
		1 -> 1000ms + to avoid of losing ms
	*/
}

//Accurate thread blocking for a given time
void	blocking_time(time_t ms)
{
	time_t	start;

	start = get_ms_time();
	while (get_ms_Time() - start < ms)
		usleep(100);
}

