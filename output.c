#include "philo.h"

int	print(t_philo *philo, int flag)
{
	pthread_mutex_lock(&philo->next_data->mix);
	if (flag == 0)
	{
		printf("%d:philo %d is died\n",
			get_time_pass(philo->next_data->time_start), philo->name);
		pthread_mutex_unlock(&philo->next_data->mix);
		return (1);
	}
	if (philo->next_data->dead == 1
		|| philo->next_data->all_eat == philo->next_data->numbers_of_times)
	{
		pthread_mutex_unlock(&philo->next_data->mix);
		return (1);
	}
	print_add(philo, flag);
	pthread_mutex_unlock(&philo->next_data->mix);
	return (0);
}

void	print_add(t_philo *philo, int flag)
{
	if (flag == 1)
		printf("%d :philo %d has taken a left fork\n",
			get_time_pass(philo->next_data->time_start), philo->name);
	else if (flag == 2)
		printf("%d :philo %d has taken a right fork\n",
			get_time_pass(philo->next_data->time_start), philo->name);
	else if (flag == 3)
		printf("%d :philo %d is eating\n",
			get_time_pass(philo->next_data->time_start), philo->name);
	else if (flag == 4)
		printf("%d :philo %d is sleeping\n",
			get_time_pass(philo->next_data->time_start), philo->name);
	else if (flag == 5)
		printf("%d :philo %d is thinking\n",
			get_time_pass(philo->next_data->time_start), philo->name);
}
