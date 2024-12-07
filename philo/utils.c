#include "../include/philo.h"

void ft_define_params(t_given *given_params, int argc, char *argv[])
{
	given_params->number_of_philosophers = atoi(argv[1]);
	if (argc == 3)
		given_params->time_to_die = atoi(argv[2]);
	if (argc == 4)
		given_params->time_to_eat = atoi(argv[3]);
	if (argc == 5)
		given_params->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		given_params->number_of_times_each_philosopher_must_eat = atoi(argv[5]);
}

void ft_cleanup(t_philo *philos, pthread_mutex_t *forks, int number_of_philosophers)
{
	unsigned int i = 0;

	while (i < number_of_philosophers)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(philos);
	free(forks);
}
