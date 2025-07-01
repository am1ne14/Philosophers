/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-am <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:09:52 by mohel-am          #+#    #+#             */
/*   Updated: 2025/07/01 18:10:00 by mohel-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
void    print_action(t_philo *philo, char *action);
long    get_time();
*/

void	print_action(t_philo *philo, char *action)
{
	long	time;

	pthread_mutex_lock(&philo->table->print);
	time = get_time() - philo->table->start_time;
	printf("%ld %d %s\n", time, philo->id, action);
	pthread_mutex_unlock(&philo->table->print);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
