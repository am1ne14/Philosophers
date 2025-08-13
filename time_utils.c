#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_action(t_philo *philo, const char *action)
{
	long	t;

	pthread_mutex_lock(&philo->table->state_mutex);
	if (!philo->table->finished)
	{
		pthread_mutex_lock(&philo->table->print);
		t = get_time() - philo->table->start_time;
		printf("%ld %d %s\n", t, philo->id, action);
		pthread_mutex_unlock(&philo->table->print);
	}
	pthread_mutex_unlock(&philo->table->state_mutex);
}

void	print_action_custom(long time, int philo_id, const char *action)
{
	printf("%ld %d %s\n", time, philo_id, action);
}

void	eat_and_update(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->philo_mutex);
	print_action(philo, "is eating");
	usleep(philo->table->time_to_eat * 1000);
}

void	philo_sleep_think(t_philo *philo)
{
	print_action(philo, "is sleeping");
	usleep(philo->table->time_to_sleep * 1000);
	print_action(philo, "is thinking");
	if (philo->table->nb_philos % 2 != 0
		&& philo->table->time_to_eat >= philo->table->time_to_sleep)
		usleep(philo->table->time_to_eat * 1000);
}
