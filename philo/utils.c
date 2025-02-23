#include "../include/philo.h"

void cleanup(t_philo *philos, pthread_mutex_t *forks)
{
	int i = 0;

	while (i < philos->given_params->number_of_philosophers)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philos->given_params->print_mutex);
	pthread_mutex_destroy(&philos->given_params->time_mutex);
	pthread_mutex_destroy(&philos->given_params->eating_mutex);
	pthread_mutex_destroy(&philos->given_params->end_mutex);
	free(philos);
	free(forks);
}

long gettime()
{
	struct timeval tv;
	long timestamp;

	gettimeofday(&tv, NULL);
	timestamp = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (timestamp);
}

long format_time(long start_time)
{
	struct timeval tv;
	long current_timestamp;
	long formatted;

	gettimeofday(&tv, NULL);
	current_timestamp = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	formatted = current_timestamp - start_time;
	return (formatted);
}