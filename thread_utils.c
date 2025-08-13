#include "philo.h"

void	set_fork_order(t_philo *philo, pthread_mutex_t **first_fork,
	pthread_mutex_t **second_fork)
{
	if (philo->id < ((philo->id % philo->table->nb_philos) + 1))
	{
		*first_fork = philo->left_fork;
		*second_fork = philo->right_fork;
	}
	else
	{
		*first_fork = philo->right_fork;
		*second_fork = philo->left_fork;
	}
}

void	init_philosophers_meal_time(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_lock(&table->philo[i].philo_mutex);
		table->philo[i].last_meal = table->start_time;
		pthread_mutex_unlock(&table->philo[i].philo_mutex);
		i++;
	}
}

int	create_philosopher_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_create(&table->philo[i].thread, NULL,
				&philo_thread, &table->philo[i]))
			return (1);
		i++;
	}
	return (0);
}

void	join_philosopher_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_join(table->philo[i].thread, NULL);
		i++;
	}
}
