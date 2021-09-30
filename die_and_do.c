#include "philo.h"

int	func_for_die2(t_philo *philo, t_parameters *parameters, int i)
{
	if (parameters->time_to_die + 1
		<= get_time_pass(parameters->time_start) - philo[i].last_meal)
	{
		parameters->dead = 1;
		print(&philo[i], 0);
		return (1);
	}
	if (philo[i].count_of_eat == parameters->numbers_of_times)
	{
		parameters->all_eat++;
		if (parameters->all_eat == parameters->count_philo)
		{
			printf("%d:all philosophers ate\n",
				get_time_pass(parameters->time_start));
			return (1);
		}
	}
	return (0);
}

void	*func_for_die(void *tmp)
{
	t_philo			*philo;
	t_parameters	*param;
	int				i;

	philo = tmp;
	param = philo[0].next_data;
	while (1)
	{
		i = 0;
		param->all_eat = 0;
		while (i < param->count_philo)
		{
			if (func_for_die2(philo, param, i))
				return (NULL);
			i++;
			func_for_wait(1);
		}
	}
	return (NULL);
}

void	*func_for_philo(void *temp)
{
	t_philo	*philo;

	philo = temp;
	if (philo->name % 2 == 0)
		func_for_wait((int)philo->next_data->time_to_eat);
	while (philo->next_data->dead != 1
		&& philo->count_of_eat != philo->next_data->numbers_of_times)
	{
		pthread_mutex_lock(philo->left_fork);
		if (print(philo, 1))
			return (NULL);
		pthread_mutex_lock(philo->right_fork);
		if (print(philo, 2))
			return (NULL);
		philo_eat(philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
