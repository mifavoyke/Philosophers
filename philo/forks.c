#include "../include/philo.h"

pthread_mutex_t *initialise_forks(int number_of_philosophers)
{
	pthread_mutex_t *forks;
	int i = 0;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * number_of_philosophers);
	if (!forks)
		return (NULL);
	while (i < number_of_philosophers)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

void assign_forks(t_philo *philos, pthread_mutex_t *forks, int number_of_philosophers)
{
	int i = 0;

	while (i < number_of_philosophers)
	{
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % number_of_philosophers];
		i++;
	}
}
