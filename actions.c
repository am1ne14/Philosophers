#include "philo.h"

/*
void	unlock_forks(t_philo *philo, int *l, int *r);
void	take_forks(t_philo *philo, int *l, int *r);
void	eat_and_update(t_philo *philo);
void	philo_sleep_think(t_philo *philo);
 */

void	unlock_forks(t_philo *philo, int *l, int *r)
{
	if (*l)
		pthread_mutex_unlock(philo->left_fork);
	if (*r)
		pthread_mutex_unlock(philo->right_fork);
	*l = 0;
	*r = 0;
}

void	take_forks(t_philo *philo, int *l, int *r)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	int				*first_flag;
	int				*second_flag;

	if (philo->id < ((philo->id % philo->table->nb_philos) + 1))
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
		first_flag = l;
		second_flag = r;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
		first_flag = r;
		second_flag = l;
	}
	
	pthread_mutex_lock(first_fork);
	*first_flag = 1;
	if (is_finished(philo))
	{
		unlock_forks(philo, l, r);
		return ;
	}
	print_action(philo, "has taken a fork");
	
	pthread_mutex_lock(second_fork);
	*second_flag = 1;
	if (is_finished(philo))
	{
		unlock_forks(philo, l, r);
		return ;
	}
	print_action(philo, "has taken a fork");
}

void	eat_and_update(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->philo_mutex);
	print_action(philo, "is eating");
	ft_msleep(philo->table->time_to_eat, philo->table);
}

void	philo_sleep_think(t_philo *philo)
{
	print_action(philo, "is sleeping");
	ft_msleep(philo->table->time_to_sleep, philo->table);
	print_action(philo, "is thinking");
	if (philo->table->nb_philos % 2 != 0 
		&& philo->table->time_to_eat >= philo->table->time_to_sleep)
		usleep(philo->table->time_to_eat * 1000);
}
