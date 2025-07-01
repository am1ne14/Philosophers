/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-am <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:09:04 by mohel-am          #+#    #+#             */
/*   Updated: 2025/07/01 18:11:49 by mohel-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*

void    put_fork(t_philo *philo);
void    philo_eat(t_philo *philo);;
void    take_fork(t_philo *philo);
void    philo_sleep_think(t_philo *philo);

*/

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, "has taken a fork");
}

void	philo_sleep_think(t_philo *philo)
{
	print_action(philo, "is sleeping");
	usleep(philo->table->time_to_sleep * 1000);
	print_action(philo, "is_thinking");
}

void	philo_eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->table->print);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->table->print);
	print_action(philo, "is eating");
	usleep(philo->table->time_to_eat * 1000);
	philo->meals_eaten++;
	put_forks(philo);
}
