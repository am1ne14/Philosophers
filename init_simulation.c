/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-am <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:09:29 by mohel-am          #+#    #+#             */
/*   Updated: 2025/07/01 18:18:51 by mohel-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
int init_simulation(int ac, char **av, t_table *table);
int parse_args(int ac, char **av, t_table *table);
int init_mutexes(t_table *table);
int init_philos(t_table *table);

*/

int	init_simulation(int ac, char **av, t_table *table)
{
	if (parse_args(ac, av, table))
	{
		printf("Invalid arguments\n");
		return (1);
	}
	if (init_mutexes(table))
	{
		printf("Mutex initalisation failed\n");
		return (1);
	}
	if (init_philos(table))
	{
		printf("Philosophers Initalidation failed\n");
		return (1);
	}
	return (0);
}

int	parse_args(int ac, char **av, t_table *table)
{
	if (ac != 5 && ac != 6)
		return (1);
	table->nb_philos = atoi(av[1]);
	table->time_to_die = atoi(av[2]);
	table->time_to_eat = atoi(av[3]);
	table->time_to_sleep = atoi(av[4]);
	table->nb_meals = -1;
	if (ac == 6)
		table->nb_meals = atoi(av[5]);
	if (table->nb_philos < 1 || table->time_to_die < 1 || table->time_to_eat < 1
		|| table->time_to_sleep < 1 || (ac == 6 && table->nb_meals < 1))
		return (1);
	table->finished = 0;
	return (0);
}

int	init_philos(t_table *table)
{
	int	i;

	i = 0;
	table->philo = malloc(sizeof(t_philo) * table->nb_philos);
	if (!table->philo)
		return (1);
	while (i < table->nb_philos)
	{
		table->philo[i].id = i + 1;
		table->philo[i].meals_eaten = 0;
		table->philo[i].last_meal = 0;
		table->philo[i].table = table;
		table->philo[i].left_fork = &table->fork[i];
		table->philo[i].right_fork = &table->fork[(i + 1) % table->nb_philos];
		i++;
	}
	return (0);
}

int	init_mutexes(t_table *table)
{
	int	i;

	i = 0;
	table->fork = malloc(sizeof(pthread_mutex_t) * table->nb_philos);
	if (!table->fork)
		return (1);
	while (i < table->nb_philos)
	{
		if (pthread_mutex_init(&table->fork[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&table->print, NULL))
		return (1);
	return (0);
}
