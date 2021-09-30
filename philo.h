#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_parameters
{
	int				count_philo;
	long			time_to_eat;
	long			time_to_die;
	long			time_to_sleep;
	int				numbers_of_times;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	mix;
	long			time_start;
	int				all_eat;
	int				dead;
	struct s_philo	*next_ph;
}				t_parameters;

typedef struct s_philo
{
	int					name;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	int					count_of_eat;
	long				last_meal;
	struct s_parameters	*next_data;
}				t_philo;

void	func_for_wait(int s);
int		ft_atoi(char *str);
int		check(int argc, char **argv);
void	struct_init(t_parameters *parameters, char **argv, int argc);
void	create_pthreads(t_parameters *parameters);
void	*func_for_die(void *tmp);
void	create_loop(t_parameters *parameters,
			t_philo *philo, pthread_t *thread);
int		func_for_die2(t_philo *philo, t_parameters *parameters, int i);
void	create_loop(t_parameters *parameters,
			t_philo *philo, pthread_t *thread);
void	*func_for_philo(void *temp);
void	philo_think(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_eat(t_philo *philo);
void	print_add(t_philo *philo, int flag);
int		get_time_pass(long start);
int		print(t_philo *philo, int flag);
long	get_moment(void);

#endif