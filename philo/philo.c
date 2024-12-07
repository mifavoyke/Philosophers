#include "../include/philo.h"

int main(int argc, char *argv[])
{
    t_given given_params;
    t_philo *philos = NULL;
    pthread_mutex_t *forks = NULL;
    pthread_t supervisor;

    if (argc < 2)
    {
        printf("Invalid input.\n");
        return (0);
    }
    given_params.number_of_philosophers = atoi(argv[1]);
    given_params.time_to_die = atoi(argv[2]);
    philos->given_params = &given_params;
    ft_create_philo(&philos, &forks, &given_params);
    ft_cleanup(philos, forks, given_params.number_of_philosophers);
    return (0);
}
