#include "../include/philo.h"

void kill_threads(t_philo *philos)
{
	unsigned int i;

	i = 0;
	while (i < philos[0].given_params->number_of_philosophers)
	{
		pthread_detach(philos[i].philosopher);
		i++;
	}
}

int monitor(t_philo *philos)
{
	unsigned int i;
	unsigned long death_time;
	unsigned long current_time;

	i = 0;
	while (i < philos[0].given_params->number_of_philosophers)
	{
		death_time = philos[i].last_meal_time + philos[i].given_params->time_to_die;
		pthread_mutex_lock(&philos[i].given_params->time_mutex);
		current_time = gettime();
		// current_time = 1739268231024;
		pthread_mutex_unlock(&philos[i].given_params->time_mutex);
		if (death_time <= current_time)
		{
			kill_threads(philos);
			printf("%ld %d died\n", current_time, philos[i].id);
			return (1);
		}
		i++;
	}
	if (usleep(10 * 1000))
		perror("usleep");
	return (0);
}

void *supervise(void *arg)
{
	t_philo *philos;

	philos = (t_philo *)arg;
	while (1)
	{
		if (monitor(philos) > 0)
			return(NULL);
	}
	return (NULL);
}
