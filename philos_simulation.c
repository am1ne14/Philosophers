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
	ft_msleep(p->table->time_to_die, p->table);
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
	while (get_time() < p->table->start_time)
		usleep(100);
	if (p->table->nb_philos == 1)
	{
		handle_single_philo(p);
		return (NULL);
	}
	if (p->id % 2 == 0)
		usleep(p->table->time_to_eat * 500);
	philo_routine(p);
	return (NULL);
}

int	start_simulation(t_table *table)
{
	int	i;
	int	err;

	table->start_time = get_time();
	i = 0;
	while (i < table->nb_philos)
	{
		table->philo[i].last_meal = table->start_time;
		if (pthread_create(&table->philo[i].thread, NULL,
				&philo_thread, &table->philo[i]))
			return (1);
		i++;
	}
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
