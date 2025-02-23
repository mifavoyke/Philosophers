/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:18:14 by yhusieva          #+#    #+#             */
/*   Updated: 2025/02/23 20:23:30 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	take_fork(t_philo *philo)
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
	print_log(philo, "has taken a fork", "\033[0m");
	return (0);
}

int	ft_eating(t_philo *philo)
{
	if (take_fork(philo))
		return (1);
	if (check_end(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	print_log(philo, "is eating", "\033[38;5;93m");
	pthread_mutex_lock(&philo->given_params->time_mutex);
	philo->last_meal_time = format_time(philo[0].given_params->start_time)
		+ philo->given_params->time_to_eat;
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
