#include "philo.h"
/*
long	get_time(void);
void	print_action(t_philo *philo, const char *action);
void	print_action_custom(long time, int philo_id, const char *action);
int		ft_atoi(const char *str);
*/

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || 
			c == '\v' || c == '\f' || c == '\r');
}

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;
	int		i;

	if (!str || !*str)
		return (0);
	result = 0;
	sign = 1;
	i = 0;
	// Skip whitespace
	while (str[i] && ft_isspace(str[i]))
		i++;
	// Handle sign
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	// Must have at least one digit after sign/whitespace
	if (!str[i] || !ft_isdigit(str[i]))
		return (0);
	// Convert digits
	while (str[i] && ft_isdigit(str[i]))
	{
		// Check for overflow before multiplication
		if (result > (2147483647 - (str[i] - '0')) / 10)
		{
			if (sign == 1)
				return (2147483647); // INT_MAX
			else
				return (-2147483648); // INT_MIN
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	// Check for trailing non-whitespace characters
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i])
		return (0); // Invalid input - non-digit, non-whitespace characters
	return ((int)(result * sign));
}

int	is_valid_number(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	// Skip whitespace
	while (str[i] && ft_isspace(str[i]))
		i++;
	// Handle optional sign
	if (str[i] == '+' || str[i] == '-')
		i++;
	// Must have at least one digit
	if (!str[i] || !ft_isdigit(str[i]))
		return (0);
	// Check all remaining characters are digits
	while (str[i] && ft_isdigit(str[i]))
		i++;
	// Skip trailing whitespace
	while (str[i] && ft_isspace(str[i]))
		i++;
	// Should be at end of string
	return (str[i] == '\0');
}
long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_action(t_philo *philo, const char *action)
{
	long	t;

	pthread_mutex_lock(&philo->table->state_mutex);
	if (!philo->table->finished)
	{
		pthread_mutex_lock(&philo->table->print);
		t = get_time() - philo->table->start_time;
		printf("%ld %d %s\n", t, philo->id, action);
		pthread_mutex_unlock(&philo->table->print);
	}
	pthread_mutex_unlock(&philo->table->state_mutex);
}

void	print_action_custom(long time, int philo_id, const char *action)
{
	printf("%ld %d %s\n", time, philo_id, action);
}

void	ft_msleep(long time_ms, t_table *table)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time_ms)
	{
		pthread_mutex_lock(&table->state_mutex);
		if (table->finished)
		{
			pthread_mutex_unlock(&table->state_mutex);
			break ;
		}
		pthread_mutex_unlock(&table->state_mutex);
		usleep(50);
	}
}
