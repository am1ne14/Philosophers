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

static int	parse_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

static long	parse_digits(const char *str, int *i, int sign)
{
	long	result;

	result = 0;
	while (str[*i] && ft_isdigit(str[*i]))
	{
		if (result > (2147483647 - (str[*i] - '0')) / 10)
		{
			if (sign == 1)
				return (2147483647);
			else
				return (-2147483648);
		}
		result = result * 10 + (str[*i] - '0');
		(*i)++;
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;
	int		i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	sign = parse_sign(str, &i);
	if (!str[i] || !ft_isdigit(str[i]))
		return (0);
	result = parse_digits(str, &i, sign);
	if (result == 2147483647 || result == -2147483648)
		return ((int)result);
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i])
		return (0);
	return ((int)(result * sign));
}
