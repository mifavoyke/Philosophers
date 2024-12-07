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

void ft_assign_forks(t_philo *philos, pthread_mutex_t *forks, int number_of_philosophers)
{
    unsigned int i = 0;

    while (i < number_of_philosophers)
    {
        philos[i].left_fork = &forks[i];
        philos[i].right_fork = &forks[(i + 1) % number_of_philosophers];
        printf("Philosopher %d has left fork %d and right fork %d.\n", philos[i].id, i, (i + 1) % number_of_philosophers);
        i++;
    }
}

void ft_create_philosopher_threads(t_philo *philos, t_given *given_params)
{
    unsigned int i = 0;

    while (i < given_params->number_of_philosophers)
    {
        philos[i].id = i;
        pthread_create(&philos[i].philosopher, NULL, ft_routine, &philos[i]);
        i++;
    }
}

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

void ft_create_philo(t_philo **philos, pthread_mutex_t **forks, t_given *given_params)
{
    *philos = (t_philo *)malloc(sizeof(t_philo) * given_params->number_of_philosophers);
    if (!*philos)
        return;
    
    *forks = ft_initialize_forks(given_params->number_of_philosophers);
    if (!*forks)
    {
        free(*philos);
        return ;
    }
    ft_create_philosopher_threads(*philos, given_params);
    ft_assign_forks(*philos, *forks, given_params->number_of_philosophers);
    ft_join_philosopher_threads(*philos, given_params->number_of_philosophers);
}
