/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_simlation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-am <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:09:43 by mohel-am          #+#    #+#             */
/*   Updated: 2025/07/01 18:09:48 by mohel-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*

int		start_simulation(t_table *table)
void	*philo_routine(void *arg)
void	monitor_philos(t_table *table);

*/
int	start_simulation(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = get_time();
	while (i < table->nb_philos)
	{
		table->philo[i].last_meal = table->start_time;
		if (pthread_create(&table->philo[i].thread, NULL,
				&philo_routine, &table->philo[i]))
		{
			printf("Error: Failed to create a thread");
			return (1);
		}
		i++;
	}
	if (monitor_philos(table))
		return (1);
	i = 0;
	while (i < table->nb_philos)
	{
		pthread_join(table->philo[i].thread, NULL);
		i++;
	}
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(200);
	while (!philo->table->finished)
	{
		philo_eat(philo);
		if (philo->table->nb_meals > 0
			&& philo->meals_eaten >= philo->table->nb_meals)
			break ;
		philo_sleep_think(philo);
	}
	return (NULL);
}

int	monitor_philos(t_table *table)
{
	int		i;
	long	now;

	while (!table->finished)
	{
		i = 0;
		while (i < table->nb_philos)
		{
			now = get_time();
			if (check_death(table, i, now))
				return (1);
			i++;
		}
		if (check_all(table))
			return (1);
		usleep(1000);
	}
	return (0);
}
