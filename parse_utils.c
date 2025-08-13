#include "philo.h"

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	take_second_fork(t_philo *philo, pthread_mutex_t *second_fork,
	int *second_flag)
{
	pthread_mutex_lock(second_fork);
	*second_flag = 1;
	if (is_finished(philo))
	{
		*second_flag = 0;
		pthread_mutex_unlock(second_fork);
		return (1);
	}
	print_action(philo, "has taken a fork");
	return (0);
}

int	take_first_fork(t_philo *philo, pthread_mutex_t *first_fork,
	int *first_flag)
{
	pthread_mutex_lock(first_fork);
	*first_flag = 1;
	if (is_finished(philo))
	{
		*first_flag = 0;
		pthread_mutex_unlock(first_fork);
		return (1);
	}
	print_action(philo, "has taken a fork");
	return (0);
}

int	is_valid_number(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i] || !ft_isdigit(str[i]))
		return (0);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (str[i] == '\0');
}
