#include "philo.h"

static int	are_philos_full(t_table *table)
{
	int	i;
	int	full_philos;

	i = 0;
	full_philos = 0;
	if (table->nb_meals == -1)
		return (0);
	while (i < table->nb_philos)
	{
		pthread_mutex_lock(&table->philo[i].philo_mutex);
		if (table->philo[i].meals_eaten >= table->nb_meals)
			full_philos++;
		pthread_mutex_unlock(&table->philo[i].philo_mutex);
		i++;
	}
	if (full_philos == table->nb_philos)
		return (1);
	return (0);
}

int	check_death(t_table *table, int i)
{
	long	now;
	long	last_meal_time;

	now = get_time();
	pthread_mutex_lock(&table->philo[i].philo_mutex);
	last_meal_time = table->philo[i].last_meal;
	if ((now - last_meal_time) >= table->time_to_die)
	{
		pthread_mutex_lock(&table->state_mutex);
		if (!table->finished)
		{
			table->finished = 1;
			pthread_mutex_lock(&table->print);
			printf("%ld %d died\n", now - table->start_time, table->philo[i].id);
			pthread_mutex_unlock(&table->print);
			pthread_mutex_unlock(&table->state_mutex);
			pthread_mutex_unlock(&table->philo[i].philo_mutex);
			return (1);
		}
		pthread_mutex_unlock(&table->state_mutex);
	}
	pthread_mutex_unlock(&table->philo[i].philo_mutex);
	return (0);
}

int	check_all_eaten(t_table *table)
{
	pthread_mutex_lock(&table->state_mutex);
	if (table->finished)
	{
		pthread_mutex_unlock(&table->state_mutex);
		return (0);
	}
	pthread_mutex_unlock(&table->state_mutex);
	
	if (are_philos_full(table))
	{
		pthread_mutex_lock(&table->state_mutex);
		if (!table->finished)
		{
			table->finished = 1;
			pthread_mutex_unlock(&table->state_mutex);
			return (1);
		}
		pthread_mutex_unlock(&table->state_mutex);
	}
	return (0);
}

int	monitor_philos(t_table *table)
{
	int		i;

	while (1)
	{
		i = 0;
		while (i < table->nb_philos)
		{
			if (check_death(table, i))
				return (1);
			i++;
		}
		if (check_all_eaten(table))
			return (0);
		usleep(50);
	}
	return (0);
}
