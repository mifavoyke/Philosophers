#include "../include/philo.h"

int check_end(t_philo *philo)
{
	pthread_mutex_lock(&philo[0].given_params->end_mutex);
	if (philo[0].given_params->end_flag == 1)
	{
		pthread_mutex_unlock(&philo[0].given_params->end_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo[0].given_params->end_mutex);
	return (0);
}

void ft_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->given_params->print_mutex);
	printf("\033[38;5;226m%ld %d is sleeping\033[0m\n", format_time(philo[0].given_params->start_time), philo->id);
	pthread_mutex_unlock(&philo->given_params->print_mutex);
	if (usleep(philo->given_params->time_to_sleep * 1000))
		perror("usleep");
}

void ft_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->given_params->print_mutex);
	printf("\033[38;5;45m%ld %d is thinking\033[0m\n", format_time(philo[0].given_params->start_time), philo->id);
	pthread_mutex_unlock(&philo->given_params->print_mutex);
	if (usleep(1000))
		perror("usleep");
}

// void take_fork(t_philo *philo)
// {

// }

int ft_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->given_params->time_mutex);
	philo->last_meal_time = format_time(philo[0].given_params->start_time);
	pthread_mutex_unlock(&philo->given_params->time_mutex);

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

	if (check_end(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}

	pthread_mutex_lock(&philo->given_params->print_mutex);
	printf("%ld %d has taken a fork\n", format_time(philo[0].given_params->start_time), philo->id);
	pthread_mutex_unlock(&philo->given_params->print_mutex);

	if (check_end(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}

	pthread_mutex_lock(&philo->given_params->print_mutex);
	printf("\033[38;5;93m%ld %d is eating\033[0m\n", format_time(philo[0].given_params->start_time), philo->id);
	pthread_mutex_unlock(&philo->given_params->print_mutex);

	pthread_mutex_lock(&philo->given_params->time_mutex);
	philo->last_meal_time = format_time(philo[0].given_params->start_time) + philo->given_params->time_to_eat;
	pthread_mutex_unlock(&philo->given_params->time_mutex);

	if (usleep(philo->given_params->time_to_eat * 1000))
		perror("usleep");

	pthread_mutex_lock(&philo->given_params->eating_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->given_params->eating_mutex);
	
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	
	pthread_mutex_lock(&philo->given_params->time_mutex);
	philo->last_meal_time = format_time(philo[0].given_params->start_time);
	pthread_mutex_unlock(&philo->given_params->time_mutex);
	return (0);
}

void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_end(philo))
			return (NULL);
		if (ft_eating(philo))
			return (NULL);
		if (check_end(philo))
			return (NULL);
		ft_sleeping(philo);
		if (check_end(philo))
			return (NULL);
		ft_thinking(philo);
		if (check_end(philo))
			return (NULL);
	}
	return (NULL);
}
