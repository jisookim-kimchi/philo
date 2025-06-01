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
			pthread_mutex_destroy(&table->philos[i].meal_mutex);
			pthread_mutex_destroy(&table->philos[i].state_mutex);
			i++;
		}
		free(table->philos);
	}
	if (table->forks)
	{
		while (i < table->philo_num)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
		free(table->forks);
	}
	//if (&table->someone_died_mutex)
		pthread_mutex_destory(&table->someone_died_mutex);
	//if (&table->print_mutex)
		pthread_mutex_destory(&table->print_mutex);
	free(table);
}
