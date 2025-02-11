#include "../include/philo.h"

void ft_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->given_params->print_mutex);
	pthread_mutex_lock(&philo->given_params->time_mutex);
	printf("%ld %d is sleeping\n", gettime(), philo->id);
	pthread_mutex_unlock(&philo->given_params->print_mutex);
	pthread_mutex_unlock(&philo->given_params->time_mutex);
	if (usleep(philo->given_params->time_to_sleep * 1000))
		perror("usleep");
}

void ft_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->given_params->print_mutex);
	pthread_mutex_lock(&philo->given_params->time_mutex);
	printf("%ld %d is thinking\n", gettime(), philo->id);
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
	printf("%ld %d is eating\n", gettime(), philo->id);
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
		i++;
	}
	return (NULL);
}
