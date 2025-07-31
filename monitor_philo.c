/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-am <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:10:14 by mohel-am          #+#    #+#             */
/*   Updated: 2025/07/01 18:10:15 by mohel-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
int check_death(t_table *table, int i, long now);
int check_all(t_table *table);
*/

int	check_death(t_table *table, int i, long now)
{
	if ((now - table->philo[i].last_meal) >= table->time_to_die)
	{
		pthread_mutex_lock(&table->print);
		printf("%ld %d died\n", now - table->start_time, table->philo[i].id);
		pthread_mutex_unlock(&table->print);
		table->finished = 1;
		return (1);
	}
	return (0);
}

int	check_all(t_table *table)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	if (table->nb_meals <= 0)
		return (0);
	while (i < table->nb_philos)
	{
		if (table->philo[i].meals_eaten >= table->nb_meals)
			full++;
		i++;
	}
	if (full == table->nb_philos)
	{
		table->finished = 1;
		return (1);
	}
	return (0);
}
