#include "philo.h"

/*
int	parse_args(int ac, char **av, t_table *table);
int	init_philos(t_table *table);
int	init_simulation(int ac, char **av, t_table *table);
*/

int	parse_args(int ac, char **av, t_table *table)
{
	if (ac != 5 && ac != 6)
		return (1);
	if (!is_valid_number(av[1]) || !is_valid_number(av[2])
		|| !is_valid_number(av[3]) || !is_valid_number(av[4]))
		return (1);
	if (ac == 6 && !is_valid_number(av[5]))
		return (1);
	table->nb_philos = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->nb_meals = ft_atoi(av[5]);
	else
		table->nb_meals = -1;
	if (table->nb_philos < 1 || table->nb_philos > 200
		|| table->time_to_die < 1 || table->time_to_eat < 1
		|| table->time_to_sleep < 1 || (ac == 6 && table->nb_meals < 1))
		return (1);
	table->finished = 0;
	table->all_threads_ready = 0;
	return (0);
}

int	init_philos(t_table *table)
{
	int	i;

	table->philo = malloc(sizeof(t_philo) * table->nb_philos);
	if (!table->philo)
		return (1);
	i = 0;
	while (i < table->nb_philos)
	{
		table->philo[i].id = i + 1;
		table->philo[i].meals_eaten = 0;
		table->philo[i].last_meal = 0;
		table->philo[i].table = table;
		if (pthread_mutex_init(&table->philo[i].philo_mutex, NULL))
			return (1);
		table->philo[i].left_fork = &table->forks[i];
		table->philo[i].right_fork = &table->forks[(i + 1) % table->nb_philos];
		i++;
	}
	return (0);
}

int	init_simulation(int ac, char **av, t_table *table)
{
	if (parse_args(ac, av, table))
		return (1);
	if (init_mutexes(table))
		return (1);
	if (init_philos(table))
	{
		cleanup_mutexes(table);
		return (1);
	}
	return (0);
}
