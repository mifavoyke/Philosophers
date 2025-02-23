#include "../include/philo.h"

int monitor(t_philo *philos, int philo_count, long max_lifetime)
{
	int i;
	long death_time;
	long current_time;
	int full_philos = 1;

	i = 0;
	while (i < philo_count)
	{
		pthread_mutex_lock(&philos[i].given_params->eating_mutex);
		if (philos[i].meals_eaten == philos[i].given_params->meal_goal)
			full_philos++;
		pthread_mutex_unlock(&philos[i].given_params->eating_mutex);

		pthread_mutex_lock(&philos[i].given_params->time_mutex);
		death_time = philos[i].last_meal_time + max_lifetime;
		pthread_mutex_unlock(&philos[i].given_params->time_mutex);

		current_time = format_time(philos[i].given_params->start_time);
		if (current_time >= death_time)
		{
			pthread_mutex_lock(&philos[0].given_params->end_mutex);
			philos[0].given_params->end_flag = 1;
			pthread_mutex_unlock(&philos[0].given_params->end_mutex);
			pthread_mutex_lock(&philos[0].given_params->print_mutex);
			printf("\033[38;5;208m%ld %d died\033[0m\n", format_time(philos[0].given_params->start_time), philos[0].id);
			pthread_mutex_unlock(&philos[0].given_params->print_mutex);
			return (1);
		}
		i++;
	}

	if (full_philos >= philo_count)
	{
		pthread_mutex_lock(&philos[0].given_params->end_mutex);
		philos[0].given_params->end_flag = 1;
		pthread_mutex_unlock(&philos[0].given_params->end_mutex);
		return (1);
	}
	if (usleep(10 * 1000))
		perror("usleep");
	return (0);
}

void *supervise(void *arg)
{
	t_philo *philos;
	int philo_count;
	long max_lifetime;

	philos = (t_philo *)arg;
	philo_count = philos->given_params->number_of_philosophers;
	max_lifetime = philos->given_params->time_to_die;
	while (1)
	{
		if (monitor(philos, philo_count, max_lifetime))
			return (NULL);
	}
	return (NULL);
}
