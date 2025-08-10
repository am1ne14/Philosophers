#include "philo.h"

/*
int	init_fork_mutexes(t_table *table);
int	init_table_mutexes(t_table *table);
int	init_mutexes(t_table *table);
 */

int	init_fork_mutexes(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philos);
	if (!table->forks)
		return (1);
	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
		{
			cleanup_forks(table, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_table_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->print, NULL))
	{
		cleanup_forks(table, table->nb_philos);
		return (1);
	}
	if (pthread_mutex_init(&table->state_mutex, NULL))
	{
		pthread_mutex_destroy(&table->print);
		cleanup_forks(table, table->nb_philos);
		return (1);
	}
	return (0);
}

int	init_mutexes(t_table *table)
{
	if (init_fork_mutexes(table))
		return (1);
	if (init_table_mutexes(table))
		return (1);
	return (0);
}
