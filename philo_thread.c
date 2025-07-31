#include "philo.h"

/*
void	*philo_thread(void *arg);
void    print_action(t_philo *philo, char *action);
void    philo_eat(t_philo *philo);
void    take_forks(t_philo *philo);
void    put_fork(t_philo *philo);
void    philo_sleep_think(t_philo *philo);
long    get_time(void);

*/

void	*philo_thread(void *arg)
{
    t_philo *philo;

    philo = (t_philo *) arg;
    if (philo->id % 2 == 0)
        usleep(200);
        while(!philo->table->finished)
        {
            philo_eat(philo);
            if (philo->table->nb_meals > 0 && philo->meals_eaten >= philo->table->nb_meals)
                break;
            philo_sleep_think(philo);
        }
        return NULL;

}

void    print_action(t_philo *philo, char *action)
{
    long    time;

    pthread_mutex_lock(&philo->table->print);
    time = get_time() -philo->table->start_time;
    printf("%ld %d %s\n", time, philo->id, action);
    pthread_mutex_unlock(&philo->table->print);
}
void    philo_eat(t_philo *philo)
{
    take_forks(philo);
    pthread_mutex_lock(&philo->table->print);
    philo->last_meal = get_time();
    pthread_mutex_unlock(&philo->table->print);
    print_action(philo, "is_eating");
    usleep(philo->table->time_to_eat * 1000);
    philo->meals_eaten++;
    put_fork(philo);
}

void    take_forks(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    print_action(philo, "has taken a fork");
    pthread_mutex_lock(philo->right_fork);
    print_action(philo, "has taken a fork");
}

void    put_fork(t_philo *philo)
{
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);    
}

void    philo_sleep_think(t_philo *philo)
{
    print_action(philo, "is sleeping");
    usleep(philo->table->time_to_sleep * 1000);
    print_action(philo, "is thinking");
}

long    get_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));    
}


void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
