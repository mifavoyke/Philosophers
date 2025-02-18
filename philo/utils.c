#include "../include/philo.h"

void ft_cleanup(t_philo *philos, pthread_mutex_t *forks)
{
	unsigned int i = 0;

	while (i < philos->given_params->number_of_philosophers)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philos->given_params->print_mutex);
	pthread_mutex_destroy(&philos->given_params->time_mutex);
	pthread_mutex_destroy(&philos->given_params->end_mutex);
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
