#include "philo.h"
/*
long	get_time(void);
void	print_action(t_philo *philo, const char *action);
void	print_action_custom(long time, int philo_id, const char *action);
*/
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

void	ft_msleep(long time_ms, t_table *table)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time_ms)
	{
		pthread_mutex_lock(&table->state_mutex);
		if (table->finished)
		{
			pthread_mutex_unlock(&table->state_mutex);
			break ;
		}
		pthread_mutex_unlock(&table->state_mutex);
		usleep(50);
	}
}
