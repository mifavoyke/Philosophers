#include "../include/philo.h"

void join_philosopher_threads(t_philo *philos, unsigned int number_of_philosophers)
{
	unsigned int i = 0;

	while (i < number_of_philosophers)
	{
		pthread_join(philos[i].philosopher, NULL);
		i++;
	}
	// pthread_join(*philos[i].given_params->supervisor_thread, NULL);
}

void create_philosopher_threads(t_philo *philos, t_given *given_params)
{
	unsigned int i = 0;
	int err;

	while (i < given_params->number_of_philosophers)
	{
		philos[i].id = i + 1;
		philos[i].given_params = given_params;
		philos[i].number_of_meals_eaten = 0;
		pthread_mutex_lock(&philos[i].given_params->time_mutex);
		philos[i].last_meal_time = gettime();
		pthread_mutex_unlock(&philos[i].given_params->time_mutex);
		err = pthread_create(&philos[i].philosopher, NULL, (void *)routine, &philos[i]);
		if (err)
			fprintf(stderr, "pthread_create failed: %s\n", strerror(err));
		i++;
	}
	err = pthread_create(&given_params->supervisor_thread, NULL, (void *)supervise, &philos[0]);
	if (err)
		fprintf(stderr, "pthread_create failed: %s\n", strerror(err));
}

void create_philo(t_philo **philos, pthread_mutex_t **forks, t_given *given_params)
{
	*philos = (t_philo *)malloc(sizeof(t_philo) * given_params->number_of_philosophers);
	if (!*philos)
		return;
	*forks = initialise_forks(given_params->number_of_philosophers);
	if (!*forks)
	{
		free(*philos);
		return;
	}
	assign_forks(*philos, *forks, given_params->number_of_philosophers);
	create_philosopher_threads(*philos, given_params);
	join_philosopher_threads(*philos, given_params->number_of_philosophers);
}
