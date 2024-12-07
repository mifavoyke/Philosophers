#include "../include/philo.h"

long long gettime()
{
	struct timeval tv;
	long long timestamp;

	gettimeofday(&tv, NULL);
	timestamp = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (timestamp);
}

void *ft_routine(void *arg)
{
	t_philo *philo;
	int i = 0;

	philo = (t_philo *)arg;
	while (i <= 3)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
		printf("%lld %d has taken a fork\n", gettime(), philo->id);
		printf("%lld %d is eating\n", gettime(), philo->id);
		usleep(philo->given_params->time_to_eat);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		i++;
	}
	return (NULL);
}
