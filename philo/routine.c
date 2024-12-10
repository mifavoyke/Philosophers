#include "../include/philo.h"

void ft_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->given_params->print_mutex);
	printf("%lld %d is sleeping\n", gettime(), philo->id);
	pthread_mutex_unlock(&philo->given_params->print_mutex);
	usleep(philo->given_params->time_to_sleep * 1000);
}

void ft_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->given_params->print_mutex);
	printf("%lld %d is thinking\n", gettime(), philo->id);
	pthread_mutex_unlock(&philo->given_params->print_mutex);
	usleep(1000);
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
	printf("%lld %d has taken a fork\n", gettime(), philo->id);
	printf("%lld %d is eating\n", gettime(), philo->id);
	pthread_mutex_unlock(&philo->given_params->print_mutex);
	usleep(philo->given_params->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void *ft_routine(void *arg)
{
	t_philo *philo;
	int i = 0;

	philo = (t_philo *)arg;
	while (i < 3)
	{
		ft_eating(philo);
		ft_sleeping(philo);
		ft_thinking(philo);
		i++;
	}
	return (NULL);
}
