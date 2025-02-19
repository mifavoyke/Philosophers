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
	pthread_mutex_lock(&philos[0].given_params->end_mutex);
	philos[0].given_params->end_flag = 1;
	pthread_mutex_unlock(&philos[0].given_params->end_mutex);
}

int monitor(t_philo *philos, unsigned int philo_count, unsigned long max_lifetime)
{
	unsigned int i;
	unsigned long death_time;
	unsigned long current_time;

	i = 0;
	while (i < philo_count)
	{
		death_time = philos[i].last_meal_time + max_lifetime;
		pthread_mutex_lock(&philos[i].given_params->time_mutex);
		current_time = gettime();
		pthread_mutex_unlock(&philos[i].given_params->time_mutex);
		// printf("death time: %ld for %d\n", death_time, philos[i].id);
		// printf("current time: %ld\n", current_time);
		if (current_time >= death_time)
		{
			kill_threads(philos);
			printf("\033[38;5;208m%ld %d died\033[0m\n", current_time, philos[i].id);
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
	unsigned int philo_count;
	unsigned long max_lifetime;

	philos = (t_philo *)arg;
	philo_count = philos->given_params->number_of_philosophers;
	max_lifetime = philos->given_params->time_to_die;
	while (1)
	{
		if (monitor(philos, philo_count, max_lifetime) > 0)
			return (NULL);
	}
	return (NULL);
}
