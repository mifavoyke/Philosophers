#include "../include/philo.h"

pthread_mutex_t *ft_initialize_forks(int number_of_philosophers)
{
	pthread_mutex_t *forks;
	unsigned int i = 0;

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

void ft_assign_forks(t_philo *philos, pthread_mutex_t *forks, int number_of_philosophers)
{
	unsigned int i = 0;

	while (i < number_of_philosophers)
	{
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % number_of_philosophers];
		printf("Philosopher has left fork %d and right fork %d.\n", i, (i + 1) % number_of_philosophers);
		i++;
	}
}
