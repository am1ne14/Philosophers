#include "inc/philo.h"

/*
int	init_philos(t_rules *rules);
int	init_mutexes(t_rules *rules);
int parse_args(t_rules *rules, int ac, char **av);
int	init_all(t_rules *rules, int ac, char **av);
*/


int	init_all(t_rules *rules, int ac, char **av)
{
	if (parse_args(rules, ac, av))
	{
		printf("Invalid arguments\n");
		return (1);
	}
	if (init_mutexes(rules))
	{
		printf("Mutex initialization failed\n");
		return (1);
	}
	if (init_philos(rules))
	{
		printf("Philosophers initialization failed\n");
		return (1);
	}
	// Optionally set rules->start_time
	return (0);
}

int parse_args(t_rules *rules, int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (1);
	rules->nb_philo = atoi(av[1]);
	rules->time_to_die = atoi(av[2]);
	rules->time_to_eat = atoi(av[3]);
	rules->time_to_sleep = atoi(av[4]);
	rules->nb_meals = -1; 
	if (ac == 6)
		rules->nb_meals = atoi(av[5]);
		if (rules->nb_philo < 1 || rules->time_to_die < 1
			|| rules->time_to_eat < 1 || rules->time_to_sleep < 1
			|| (ac == 6 && rules->nb_meals < 1))
			return (1);
	rules->finished = 0;
	return (0);
}
int	init_mutexes(t_rules *rules)
{
	int	i;

	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
	if (!rules->forks)
		return (1);
	i = 0;
	while (i < rules->nb_philo)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&rules->print, NULL) != 0)
		return (1);
	return (0);
}

int	init_philos(t_rules *rules)
{
	int	i;

	rules->philos = malloc(sizeof(t_philo) * rules->nb_philo);
	if (!rules->philos)
		return (1);
	i = 0;
	while (i < rules->nb_philo)
	{
		rules->philos[i].id = i + 1;
		rules->philos[i].meals_eaten = 0;
		rules->philos[i].last_meal = 0;
		rules->philos[i].rules = rules;
		rules->philos[i].left_fork = &rules->forks[i];
		rules->philos[i].right_fork = &rules->forks[(i + 1) % rules->nb_philo];
		i++;
	}
	return (0);
}
