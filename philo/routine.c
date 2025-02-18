#include "../include/philo.h"

int check_end(t_philo *philos)
{
	pthread_mutex_lock(&philos[0].given_params->end_mutex);
	if (philos[0].given_params->end_flag == 1)
	{
		pthread_mutex_unlock(&philos[0].given_params->end_mutex);
		return(1);
	}
	pthread_mutex_unlock(&philos[0].given_params->end_mutex);
	return(0);
}

void ft_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->given_params->print_mutex);
	pthread_mutex_lock(&philo->given_params->time_mutex);
	printf("\033[38;5;226m%ld %d is sleeping\033[0m\n", gettime(), philo->id);
	pthread_mutex_unlock(&philo->given_params->print_mutex);
	pthread_mutex_unlock(&philo->given_params->time_mutex);
	if (usleep(philo->given_params->time_to_sleep * 1000))
		perror("usleep");
}

void ft_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->given_params->print_mutex);
	pthread_mutex_lock(&philo->given_params->time_mutex);
	printf("\033[38;5;45m%ld %d is thinking\033[0m\n", gettime(), philo->id);
	pthread_mutex_unlock(&philo->given_params->print_mutex);
	pthread_mutex_unlock(&philo->given_params->time_mutex);
	if (usleep(1000))
		perror("usleep");
}

void ft_eating(t_philo *philo)
{
	if (philo->id < philo->given_params->number_of_philosophers - 1)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	pthread_mutex_lock(&philo->given_params->print_mutex);
	pthread_mutex_lock(&philo->given_params->time_mutex);
	printf("\033[38;5;93m%ld %d is eating\033[0m\n", gettime(), philo->id);
	pthread_mutex_unlock(&philo->given_params->print_mutex);
	pthread_mutex_unlock(&philo->given_params->time_mutex);

	if (usleep(philo->given_params->time_to_eat * 1000))
		perror("usleep");
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);

	pthread_mutex_lock(&philo->given_params->time_mutex);
	philo->last_meal_time = gettime();
	pthread_mutex_unlock(&philo->given_params->time_mutex);
	philo->number_of_meals_eaten++;
}

void *routine(void *arg)
{
	t_philo *philo;
	unsigned int i = 0;

	philo = (t_philo *)arg;
	while (i < philo->given_params->number_of_times_each_philosopher_must_eat)
	{
		ft_eating(philo);
		ft_sleeping(philo);
		ft_thinking(philo);
		if (check_end(philo) > 0)
			return(NULL);
		i++;
	}
	return (NULL);
}
