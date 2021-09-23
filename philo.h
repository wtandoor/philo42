#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>

typedef struct s_parameters
{
    int count_philo;
    int time_to_eat;
    int tine_to_die;
    int time_to_sleep;
    int numbers_of_times;
}               t_parameters;

typedef struct s_philo
{
    pthread_t *philo_n;
    t_philo *next;
}               t_philo;


int	ft_atoi(char *str);


#endif