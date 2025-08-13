#include "philo.h"

int	is_finished(t_philo *p)
{
	int	done;

	pthread_mutex_lock(&p->table->state_mutex);
	done = p->table->finished;
	pthread_mutex_unlock(&p->table->state_mutex);
	return (done);
}

void	*handle_single_philo(t_philo *p)
{
	print_action(p, "has taken a fork");
	usleep(p->table->time_to_die * 1000);
	return (NULL);
}

static void	philo_routine(t_philo *p)
{
	int	left;
	int	right;

	left = 0;
	right = 0;
	while (!is_finished(p))
	{
		take_forks(p, &left, &right);
		if (is_finished(p) || (!left && !right))
		{
			unlock_forks(p, &left, &right);
			break ;
		}
		eat_and_update(p);
		unlock_forks(p, &left, &right);
		if (is_finished(p))
			break ;
		philo_sleep_think(p);
	}
}

void	*philo_thread(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->table->nb_philos == 1)
	{
		handle_single_philo(p);
		return (NULL);
	}
	pthread_mutex_lock(&p->table->start_mutex);
	while (!p->table->all_threads_ready)
	{
		pthread_mutex_unlock(&p->table->start_mutex);
		usleep(20);
		pthread_mutex_lock(&p->table->start_mutex);
	}
	pthread_mutex_unlock(&p->table->start_mutex);
	if (p->id % 2 == 0)
		usleep(p->table->time_to_eat * 500);
	philo_routine(p);
	return (NULL);
}

int	start_simulation(t_table *table)
{
	table->start_time = get_time();
	init_philosophers_meal_time(table);
	if (create_philosopher_threads(table))
		return (1);
	pthread_mutex_lock(&table->start_mutex);
	table->all_threads_ready = 1;
	pthread_mutex_unlock(&table->start_mutex);
	monitor_philos(table);
	join_philosopher_threads(table);
	return (0);
}
