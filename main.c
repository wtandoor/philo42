#include "philo.h"

static int check(int argc, char **argv)
{
    int i;
    int j;

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

void struct_init(t_parameters *parameters, char **argv, int argc)
{
    parameters->count_philo = ft_atoi(argv[1]);
    parameters->tine_to_die = ft_atoi(argv[2]);
    parameters->time_to_eat = ft_atoi(argv[3]);
    parameters->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        parameters->numbers_of_times = ft_atoi(argv[5]);
    else
        parameters->numbers_of_times = -1;
}

void *philo_eat(t_philo *parameters)
{

}

t_philo *create_pthreads(t_parameters *parameters)
{
    t_philo *temp;
    t_philo *first;
    int i;

    first = temp;
    i = 0;
    while (i < parameters->count_philo)
    {
        temp = (t_philo *)malloc(sizeof(t_philo *));
        temp = temp->next;
        i++;
    }
    temp = NULL;
    return(first);
}

int main(int argc, char **argv)
{
    t_philo *first;
    t_parameters *parameters;
    if (check(argc, argv))
        return (0);
    parameters = (t_philo *)malloc(sizeof(t_philo));
    if (!parameters)
    {
        printf("ERROR MALLOC");
        return (0);
    }
    struct_init(parameters, argv, argc);
    first = create_pthreads(parameters);
    return(0);
}