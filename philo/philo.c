#include "../include/philo.h"

int main(int argc, char *argv[])
{
	t_given given_params;
	t_philo *philos = NULL;
	pthread_mutex_t *forks = NULL;

	if (argc < 2)
	{
		printf("Invalid input.\n");
		return (0);
	}
	ft_define_params(&given_params, argc, argv);
	ft_create_philo(&philos, &forks, &given_params);
	ft_cleanup(philos, forks, given_params.number_of_philosophers);
	return (0);
}
