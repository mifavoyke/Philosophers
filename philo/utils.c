#include "../include/philo.h"

void ft_cleanup(t_philo *philos, pthread_mutex_t *forks, int number_of_philosophers)
{
    unsigned int i = 0;

    while (i < number_of_philosophers)
    {
        pthread_mutex_destroy(&forks[i]);
        i++;
    }
    free(philos);
    free(forks);
}
