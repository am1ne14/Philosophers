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
	
	// Wait until all threads are created and ready to start
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
	int	i;
	int	err;

	// Set start time BEFORE creating threads
	table->start_time = get_time();
	
	// Initialize last_meal times for all philosophers
	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_lock(&table->philo[i].philo_mutex);
		table->philo[i].last_meal = table->start_time;
		pthread_mutex_unlock(&table->philo[i].philo_mutex);
		i++;
	}
	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_create(&table->philo[i].thread, NULL,
				&philo_thread, &table->philo[i]))
			return (1);
		i++;
	}
	pthread_mutex_lock(&table->start_mutex);
	table->all_threads_ready = 1;
	pthread_mutex_unlock(&table->start_mutex);
	
	err = monitor_philos(table);
	i = 0;
	while (i < table->nb_philos)
	{
		pthread_join(table->philo[i].thread, NULL);
		i++;
	}
	if (err)
		return (0);
	return (0);
}