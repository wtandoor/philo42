#include "philo.h"

int main(int argc, char **argv)
{
    t_parameters *parameters;
    if (check(argc, argv))
        return (0);
    parameters = (t_parameters *)malloc(sizeof(t_parameters));
    if (!parameters)
    {
        printf("ERROR MALLOC");
        return (0);
    }
    struct_init(parameters, argv, argc);
    create_pthreads(parameters);
    free(parameters);
    return(0);
}

int check(int argc, char **argv)
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
    parameters->time_to_die = ft_atoi(argv[2]);
    parameters->time_to_eat = ft_atoi(argv[3]);
    parameters->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        parameters->numbers_of_times = ft_atoi(argv[5]);
    else
        parameters->numbers_of_times = -1;
}

long get_moment(void)
{
    struct timeval t_start;
    
    gettimeofday(&t_start, NULL);    
    return(t_start.tv_sec * 1000 + t_start.tv_usec / 1000);
}

int get_time_pass(long start)
{
    return((int)(get_moment() - start));
}

int print(t_philo *philo, int flag)
{
    pthread_mutex_lock(&philo->next_data->mix);
    if (flag == 0)
    {
        printf("%d:philo %d is died\n", get_time_pass(philo->next_data->time_start), philo->name);
        pthread_mutex_unlock(&philo->next_data->mix);
        return (1);
    }
    if (philo->next_data->dead == 1 || philo->next_data->all_eat == philo->next_data->numbers_of_times)
    {
        pthread_mutex_unlock(&philo->next_data->mix);
        return (1);
    }
    print_add(philo, flag);
    pthread_mutex_unlock(&philo->next_data->mix);
    return (0);
}

void print_add(t_philo *philo, int flag)
{
    if (flag == 1)
        printf("%d :philo %d has taken a left fork\n", get_time_pass(philo->next_data->time_start), philo->name);
    else if (flag == 2)
        printf("%d :philo %d has taken a right fork\n", get_time_pass(philo->next_data->time_start), philo->name);
    else if (flag == 3)
        printf("%d :philo %d is eating\n", get_time_pass(philo->next_data->time_start), philo->name);
    else if (flag == 4)
        printf("%d :philo %d is sleeping\n", get_time_pass(philo->next_data->time_start), philo->name);
    else if (flag == 5)
        printf("%d :philo %d is thinking\n", get_time_pass(philo->next_data->time_start), philo->name);
}

void philo_eat(t_philo *philo)
{
    if (philo->next_data->dead == 1)
        return ;
    if (print(philo, 3))
        return ;
    philo->last_meal = get_time_pass(philo->next_data->time_start);
    func_for_wait((int)philo->next_data->time_to_eat);
    philo->count_of_eat++;
}

void philo_sleep(t_philo *philo)
{
    if (philo->next_data->dead)
        return ;
    if (print(philo, 4))
        return ;
    func_for_wait((int)philo->next_data->time_to_sleep);
}

void philo_think(t_philo *philo)
{
    if (philo->next_data->dead == 1)
        return ;
    if (print(philo, 5))
        return ;
}


void    *func_for_philo(void    *temp)
{
    t_philo *philo;

    philo = temp;
    if (philo->name % 2 == 0)
        func_for_wait((int)philo->next_data->time_to_eat);
    while (philo->next_data->dead != 1 && philo->count_of_eat != philo->next_data->numbers_of_times)
    {
        pthread_mutex_lock(philo->left_fork);
        if (print(philo, 1))
            return(NULL);
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

int func_for_die2(t_philo *philo, t_parameters *parameters, int i)
{
    if (parameters->time_to_die + 1 <= get_time_pass(parameters->time_start)- philo[i].last_meal)
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
            printf("%d:all philosophers ate\n", get_time_pass(parameters->time_start));
            return (1);
        }
    }
    return (0);
}

void *func_for_die(void *tmp)
{
    t_philo *philo;
    t_parameters *param;
    int i;

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

void func_for_wait(int s)
{
    long start;
    start = get_moment();
    while (get_moment() - start < s)
        usleep(50);
}

void    create_loop(t_parameters *parameters, t_philo *philo, pthread_t *thread)
{
    int i;

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

void create_pthreads(t_parameters *parameters)
{
    pthread_t   *thread;
    t_philo     *philo;
    int         i;

    i = 0;
    philo = (t_philo *)malloc(parameters->count_philo * (sizeof(t_philo)));
    thread = (pthread_t *)malloc((parameters->count_philo + 1) * (sizeof(pthread_mutex_t)));
    parameters->mutex = (pthread_mutex_t *)malloc((parameters->count_philo + 1) * (sizeof(pthread_mutex_t)));
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