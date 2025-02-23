/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:27:56 by yhusieva          #+#    #+#             */
/*   Updated: 2025/02/23 20:57:29 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	cleanup(t_philo *philos, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < philos->given_params->number_of_philosophers)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philos->given_params->print_mutex);
	pthread_mutex_destroy(&philos->given_params->time_mutex);
	pthread_mutex_destroy(&philos->given_params->eating_mutex);
	pthread_mutex_destroy(&philos->given_params->end_mutex);
	free(philos);
	free(forks);
}

long	gettime(void)
{
	struct timeval	tv;
	long			timestamp;

	gettimeofday(&tv, NULL);
	timestamp = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (timestamp);
}

long	format_time(long start_time)
{
	struct timeval	tv;
	long			current_timestamp;
	long			formatted;

	gettimeofday(&tv, NULL);
	current_timestamp = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	formatted = current_timestamp - start_time;
	return (formatted);
}

void	print_log(t_philo *philo, char *msg, char *colour)
{
	pthread_mutex_lock(&philo->given_params->print_mutex);
	printf("%s%ld %d %s\033[0m\n", colour,
		format_time(philo->given_params->start_time), philo->id, msg);
	pthread_mutex_unlock(&philo->given_params->print_mutex);
}

int	is_number(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
