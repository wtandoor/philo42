#include "philo.h"

int	ft_atoi(char *str)
{
	int	l;
	int	n;

	n = 0;
	l = 1;
	while (*str == ' ' || *str == '\v' || *str == '\t'
		|| *str == '\r' || *str == '\f' || *str == '\n')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			l = -1;
		str++;
	}
	while (*str <= '9' && *str >= '0')
	{
		n = n * 10 + (*str - '0');
		str++;
	}
	return (n * l);
}
