#include "../include/philo.h"

void init_mutexes(t_given *given_params)
{
	pthread_mutex_init(&given_params->print_mutex, NULL);
	pthread_mutex_init(&given_params->time_mutex, NULL);
	pthread_mutex_init(&given_params->eating_mutex, NULL);
	pthread_mutex_init(&given_params->end_mutex, NULL);
}

int initialise_params(t_given *given_params, int argc, char *argv[])
{
	given_params->number_of_philosophers = ft_atoi(argv[1]);
	given_params->time_to_die = ft_atoi(argv[2]);
	given_params->time_to_eat = ft_atoi(argv[3]);
	given_params->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		given_params->meal_goal = ft_atoi(argv[5]);
	else
		given_params->meal_goal = INT_MAX;
	// printf("philo count: %d\n", given_params->number_of_philosophers);
	// printf("time_to_die %ld\n", given_params->time_to_die);
	// printf("time_to_eat %ld\n", given_params->time_to_eat);
	// printf("time_to_sleep %ld\n", given_params->time_to_sleep);
	if (given_params->number_of_philosophers <= 0)
	{
		printf("\n");
		return(1);
	}
	if (given_params->time_to_die <= 0 || given_params->time_to_eat <= 0 || given_params->time_to_sleep <= 0 || given_params->meal_goal <= 0)
	{
		printf("\n");
		return(1);
	}
	given_params->end_flag = 0;
	given_params->start_time = gettime();
	init_mutexes(given_params);
	return(0);
}

int main(int argc, char *argv[])
{
	t_given given_params;
	t_philo *philos = NULL;
	pthread_mutex_t *forks = NULL;

	if (argc < 2)
	{
		printf("Invalid input.\nExpected:\nnumber_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	if (initialise_params(&given_params, argc, argv))
		return(1);
	create_philo(&philos, &forks, &given_params);
	cleanup(philos, forks);
	return (0);
}
