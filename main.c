#include "philo.h"

int	main(int argc, char **argv)
{
	t_parameters	*parameters;

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
	return (0);
}
