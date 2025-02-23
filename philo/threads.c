/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:32:52 by yhusieva          #+#    #+#             */
/*   Updated: 2025/02/23 20:34:59 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	join_philosopher_threads(t_philo *philos,
	int number_of_philosophers)
{
	int	i;

	i = 0;
	while (i < number_of_philosophers)
	{
		pthread_join(philos[i].philosopher, NULL);
		i++;
	}
	pthread_join(philos[0].given_params->supervisor_thread, NULL);
}

static void	create_philosopher_threads(t_philo *philos, t_given *given_params)
{
	int	i;

	i = 0;
	while (i < given_params->number_of_philosophers)
	{
		philos[i].id = i + 1;
		philos[i].given_params = given_params;
		philos[i].last_meal_time = format_time(given_params->start_time);
		philos[i].meals_eaten = 0;
		if (pthread_create(&philos[i].philosopher, NULL,
				(void *)routine, &philos[i]))
			printf("pthread_create\n");
		i++;
	}
	if (pthread_create(&given_params->supervisor_thread, NULL,
			(void *)supervise, &philos[0]))
		printf("pthread_create\n");
}

void	create_philo(t_philo **philos, pthread_mutex_t **forks,
			t_given *given_params)
{
	size_t	size;

	size = sizeof(t_philo) * given_params->number_of_philosophers;
	*philos = (t_philo *)malloc(size);
	if (!*philos)
		return ;
	*forks = initialise_forks(given_params->number_of_philosophers);
	if (!*forks)
		return ;
	assign_forks(*philos, *forks, given_params->number_of_philosophers);
	create_philosopher_threads(*philos, given_params);
	join_philosopher_threads(*philos, given_params->number_of_philosophers);
}
