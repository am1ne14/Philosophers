#include "philo.h"

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

	set_fork_order(philo, &first_fork, &second_fork);
	if (philo->id < ((philo->id % philo->table->nb_philos) + 1))
	{
		first_flag = l;
		second_flag = r;
	}
	else
	{
		first_flag = r;
		second_flag = l;
	}
	if (take_first_fork(philo, first_fork, first_flag))
		unlock_forks(philo, l, r);
	else if (take_second_fork(philo, second_fork, second_flag))
		unlock_forks(philo, l, r);
}
