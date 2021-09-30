#include "philo.h"

void	philo_eat(t_philo *philo)
{
	if (philo->next_data->dead == 1)
		return ;
	if (print(philo, 3))
		return ;
	philo->last_meal = get_time_pass(philo->next_data->time_start);
	func_for_wait((int)philo->next_data->time_to_eat);
	philo->count_of_eat++;
}

void	philo_sleep(t_philo *philo)
{
	if (philo->next_data->dead)
		return ;
	if (print(philo, 4))
		return ;
	func_for_wait((int)philo->next_data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	if (philo->next_data->dead == 1)
		return ;
	if (print(philo, 5))
		return ;
}
