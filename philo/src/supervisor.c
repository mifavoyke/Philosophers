/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:26:56 by yhusieva          #+#    #+#             */
/*   Updated: 2025/04/04 19:07:05 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	mark_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->given_params->end_mutex);
	philo->given_params->end_flag = 1;
	pthread_mutex_unlock(&philo->given_params->end_mutex);
}

static int	check_for_death(t_philo *philos, int i, long max_lifetime)
{
	long	death_time;
	long	current_time;

	pthread_mutex_lock(&philos[i].given_params->time_mutex);
	death_time = philos[i].last_meal_time + max_lifetime;
	pthread_mutex_unlock(&philos[i].given_params->time_mutex);
	current_time = format_time(philos[i].given_params->start_time);
	if (current_time >= death_time)
	{
		print_log(&philos[i], "died", "\033[38;5;208m");
		mark_flag(philos);
		return (1);
	}
	return (0);
}

static int	monitor(t_philo *philos, int philo_count, long max_lifetime)
{
	int	i;
	int	full_philos;

	i = 0;
	full_philos = 1;
	while (i < philo_count)
	{
		pthread_mutex_lock(&philos[i].given_params->eating_mutex);
		if (philos[i].meals_eaten >= philos[i].given_params->meal_goal)
			full_philos++;
		pthread_mutex_unlock(&philos[i].given_params->eating_mutex);
		if (check_for_death(philos, i, max_lifetime))
			return (1);
		i++;
	}
	if (full_philos >= philo_count)
	{
		mark_flag(philos);
		return (1);
	}
	if (usleep(10 * 1000))
		perror("usleep");
	return (0);
}

void	*supervise(void *arg)
{
	t_philo	*philos;
	int		philo_count;
	long	max_lifetime;

	philos = (t_philo *)arg;
	philo_count = philos->given_params->number_of_philosophers;
	max_lifetime = philos->given_params->time_to_die;
	while (1)
	{
		if (monitor(philos, philo_count, max_lifetime))
			return (NULL);
	}
	return (NULL);
}
