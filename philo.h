#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct t_rules;

typedef struct s_philo
{

	int			id;
	int			meals_eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_rules			*rules;

}	t_philo;

typedef struct s_rules
{

	int			nb_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nb_meals;
	int			finished;
	long			start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
	t_philo			*philos;

}	t_rules;


int		init_all(t_rules *rules, int argc, char **argv);
void	*philo_thread(void *arg);




#endif
