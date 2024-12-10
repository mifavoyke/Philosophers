#include "../include/philo.h"

void initialise_params(t_given *given_params, int argc, char *argv[])
{
	given_params->number_of_philosophers = atoi(argv[1]);
	given_params->time_to_die = atoi(argv[2]);
	given_params->time_to_eat = atoi(argv[3]);
	given_params->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		given_params->number_of_times_each_philosopher_must_eat = atoi(argv[5]); // look at how argc is being passed
	pthread_mutex_init(&given_params->print_mutex, NULL);

	printf("number of arguments: %d\n", argc);
	printf("number of time a philo must eat: %d\n", given_params->number_of_times_each_philosopher_must_eat);
	printf("Time to eat: %ld ms\n", given_params->time_to_eat * 1000);
	printf("Time to sleep: %ld ms\n", given_params->time_to_sleep * 1000);
}

void ft_cleanup(t_philo *philos, pthread_mutex_t *forks)
{
	unsigned int i = 0;

	while (i < philos->given_params->number_of_philosophers)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philos->given_params->print_mutex);
	free(philos);
	free(forks);
}

unsigned long gettime()
{
	struct timeval tv;
	unsigned long timestamp;

	gettimeofday(&tv, NULL);
	timestamp = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (timestamp);
}
