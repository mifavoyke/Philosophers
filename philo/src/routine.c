/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:32:21 by yhusieva          #+#    #+#             */
/*   Updated: 2025/02/23 20:35:43 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	ft_sleeping(t_philo *philo)
{
	print_log(philo, "is sleeping", "\033[38;5;226m");
	if (usleep(philo->given_params->time_to_sleep * 1000))
		perror("usleep");
}

static void	ft_thinking(t_philo *philo)
{
	print_log(philo, "is thinking", "\033[38;5;45m");
	if (usleep(1000))
		perror("usleep");
}

int	check_end(t_philo *philo)
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

void	*routine(void *arg)
{
	t_philo	*philo;

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
