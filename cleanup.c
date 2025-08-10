#include "philo.h"
/*
void	cleanup_forks(t_table *table, int count);
void	cleanup_mutexes(t_table *table);
void	cleanup_table(t_table *table);
*/

void	cleanup_forks(t_table *table, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
}

void	cleanup_mutexes(t_table *table)
{
	pthread_mutex_destroy(&table->state_mutex);
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->start_mutex);
	cleanup_forks(table, table->nb_philos);
}

void	cleanup_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_destroy(&table->philo[i].philo_mutex);
		i++;
	}
	if (table->philo)
		free(table->philo);
	cleanup_mutexes(table);
}
