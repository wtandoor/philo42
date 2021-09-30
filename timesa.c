#include "philo.h"

long	get_moment(void)
{
	struct timeval	t_start;

	gettimeofday(&t_start, NULL);
	return (t_start.tv_sec * 1000 + t_start.tv_usec / 1000);
}

int	get_time_pass(long start)
{
	return ((int)(get_moment() - start));
}

void	func_for_wait(int s)
{
	long	start;

	start = get_moment();
	while (get_moment() - start < s)
		usleep(50);
}
