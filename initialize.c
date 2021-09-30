#include "philo.h"

int	check(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		write(2, "ERROR\n", 5);
		return (1);
	}
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				write(2, "Invalid character in arguments.\n", 32);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	struct_init(t_parameters *parameters, char **argv, int argc)
{
	parameters->count_philo = ft_atoi(argv[1]);
	parameters->time_to_die = ft_atoi(argv[2]);
	parameters->time_to_eat = ft_atoi(argv[3]);
	parameters->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		parameters->numbers_of_times = ft_atoi(argv[5]);
	else
		parameters->numbers_of_times = -1;
}

void	create_loop(t_parameters *parameters, t_philo *philo, pthread_t *thread)
{
	int	i;

	i = 0;
	while (i < parameters->count_philo)
	{
		pthread_mutex_init(&parameters->mutex[i], NULL);
		philo[i].name = i + 1;
		philo[i].right_fork = &parameters->mutex[i];
		philo[i].last_meal = 0;
		philo[i].count_of_eat = 0;
		philo[i].next_data = parameters;
		parameters->next_ph = &philo[i];
		if (i != parameters->count_philo - 1)
			philo[i].left_fork = &parameters->mutex[i + 1];
		else
			philo[i].left_fork = &parameters->mutex[0];
		pthread_create(&thread[i], NULL, &func_for_philo, (void *)(&philo[i]));
		i++;
	}
	usleep(100);
	pthread_create(&thread[i], NULL, &func_for_die, (void *)(philo));
}

void	create_pthreads(t_parameters *parameters)
{
	pthread_t	*thread;
	t_philo		*philo;
	int			i;

	i = 0;
	philo = (t_philo *)malloc(parameters->count_philo
			* (sizeof(t_philo)));
	thread = (pthread_t *)malloc((parameters->count_philo + 1)
			* (sizeof(pthread_mutex_t)));
	parameters->mutex = (pthread_mutex_t *)malloc((parameters->count_philo + 1)
			* (sizeof(pthread_mutex_t)));
	parameters->dead = 0;
	pthread_mutex_init(&parameters->mix, NULL);
	parameters->time_start = get_moment();
	if (parameters->count_philo <= 0)
		return ;
	create_loop(parameters, philo, thread);
	while (i < parameters->count_philo)
		pthread_mutex_destroy(&parameters->mutex[i++]);
	pthread_join(thread[i], NULL);
	pthread_mutex_destroy(&parameters->mix);
	free(thread);
	free(philo);
	free(parameters->mutex);
}
