#include "../include/philo.h"

void *ft_routine(void *arg)
{
    t_philo *philo;
    int i = 0;

    philo = (t_philo *)arg;
    while (i <= 3)
    {
        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(philo->left_fork);
        printf("philo id - %d, meal #%d\n", philo->id, i);
        usleep(philo->given_params->time_to_eat);
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
        i++;
    }
    return (NULL);
}
