#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	philo_mutex;
	int				id;
	int				meals_eaten;
	long			last_meal;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t	start_mutex;
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals;
	int				finished;
	int				all_threads_ready;
	long			start_time;
	t_philo			*philo;
}	t_table;
//action.c
void	unlock_forks(t_philo *philo, int *l, int *r);
void	take_forks(t_philo *philo, int *l, int *r);
void	eat_and_update(t_philo *philo);
void	philo_sleep_think(t_philo *philo);
//cleanup.c
void	cleanup_forks(t_table *table, int count);
void	cleanup_mutexes(t_table *table);
void	cleanup_table(t_table *table);
//end-simulation.c
void	end_simulation(t_table *table);
//init_mutexes.c
int		init_fork_mutexes(t_table *table);
int		init_table_mutexes(t_table *table);
int		init_mutexes(t_table *table);
//init_simulation.c
int		parse_args(int ac, char **av, t_table *table);
int		init_philos(t_table *table);
int		init_simulation(int ac, char **av, t_table *table);
//monitor_philos.c
int		check_death(t_table *table, int i);
int		check_all_eaten(t_table *table);
int		monitor_philos(t_table *table);
//philos_simulation.c
int		is_finished(t_philo *p);
void	*handle_single_philo(t_philo *p);
void	*philo_thread(void *arg);
int		start_simulation(t_table *table);
//utils.c
long	get_time(void);
void	print_action(t_philo *philo, const char *action);
void	print_action_custom(long time, int philo_id, const char *action);
void	ft_msleep(long time_ms, t_table *table);
int		ft_atoi(const char *str);
int		is_valid_number(const char *str);
#endif
