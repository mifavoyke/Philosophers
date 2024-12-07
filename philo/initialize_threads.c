#include "../include/philo.h"

void ft_join_philosopher_threads(t_philo *philos, int number_of_philosophers)
{
	unsigned int i = 0;

	while (i < number_of_philosophers)
	{
		pthread_join(philos[i].philosopher, NULL);
		i++;
	}
}

void ft_create_philosopher_threads(t_philo *philos, t_given *given_params)
{
	unsigned int i = 0;

	while (i < given_params->number_of_philosophers)
	{
		philos[i].id = i;
		philos[i].given_params = given_params;
		pthread_create(&philos[i].philosopher, NULL, ft_routine, &philos[i]);
		i++;
	}
}

void ft_create_philo(t_philo **philos, pthread_mutex_t **forks, t_given *given_params)
{
	*philos = (t_philo *)malloc(sizeof(t_philo) * given_params->number_of_philosophers);
	if (!*philos)
		return;
	*forks = ft_initialize_forks(given_params->number_of_philosophers);
	if (!*forks)
	{
		free(*philos);
		return;
	}
	ft_assign_forks(*philos, *forks, given_params->number_of_philosophers);
	ft_create_philosopher_threads(*philos, given_params);
	ft_join_philosopher_threads(*philos, given_params->number_of_philosophers);
}
