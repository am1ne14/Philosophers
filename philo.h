/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-am <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:09:35 by mohel-am          #+#    #+#             */
/*   Updated: 2025/07/01 18:31:29 by mohel-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<pthread.h>
# include<sys/time.h>
# include<stdlib.h>
# include<stdio.h>
# include<unistd.h>

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals;
	int				finished;
	long			start_time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	t_philo			*philo;
}	t_table;
//actions.c
void	put_forks(t_philo *philo);
void	philo_eat(t_philo *philo);
void	take_forks(t_philo *philo);
void	philo_sleep_think(t_philo *philo);

//init_simulation.c
int		init_simulation(int ac, char **av, t_table *table);
int		parse_args(int ac, char **av, t_table *table);
int		init_mutexes(t_table *table);
int		init_philos(t_table *table);
//philos_simulation.c
int		start_simulation(t_table *table);
void	*philo_routine(void *arg);
int		monitor_philos(t_table *table);
//monitor_philo.c
int		check_death(t_table *table, int i, long now);
int		check_all(t_table *table);
//helpers.c
void	print_action(t_philo *philo, char *action);
long	get_time(void);

#endif