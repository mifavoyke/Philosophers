#include "../include/philo.h"

void initialise_params(t_given *given_params, int argc, char *argv[])
{
	given_params->number_of_philosophers = atoi(argv[1]);
	given_params->time_to_die = atoi(argv[2]);
	given_params->time_to_eat = atoi(argv[3]);
	given_params->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		given_params->number_of_times_each_philosopher_must_eat = atoi(argv[5]);
	else
		given_params->number_of_times_each_philosopher_must_eat = INT_MAX;
	pthread_mutex_init(&given_params->print_mutex, NULL);
	pthread_mutex_init(&given_params->time_mutex, NULL);
	printf("number of arguments: %d\n", argc);
	printf("number of times a philo must eat: %d\n", given_params->number_of_times_each_philosopher_must_eat);
	printf("Time to eat: %ld ms\n", given_params->time_to_eat * 1000);
	printf("Time to sleep: %ld ms\n", given_params->time_to_sleep * 1000);
}

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
	initialise_params(&given_params, argc, argv);
	create_philo(&philos, &forks, &given_params);
	ft_cleanup(philos, forks);
	return (0);
}
