# include "philo.h"

void	all_free(t_table *table)
{
	int	i;

	i = 0;
	if (!table)
		return ;
	if (table->philos)
	{
		while(i < table->philo_num)
		{
			if (table->philos[i].meal_mutex_flag)
				pthread_mutex_destroy(&table->philos[i].meal_mutex);
			if (table->philos[i].state_mutex_flag)
				pthread_mutex_destroy(&table->philos[i].state_mutex);
			i++;
		}
		free(table->philos);
	}
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
	if (table->forks_mutex_flag)
		free(table->forks_mutex_flag);
	if (table->someone_died_mutex_flag)
		pthread_mutex_destroy(&table->someone_died_mutex);
	if (table->print_mutex_flag)
		pthread_mutex_destroy(&table->print_mutex);
	free(table);
}
