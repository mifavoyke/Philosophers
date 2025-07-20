/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:18:00 by yhusieva          #+#    #+#             */
/*   Updated: 2025/02/25 20:14:09 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

pthread_mutex_t	*initialise_forks(int number_of_philosophers)
{
	pthread_mutex_t	*forks;
	int				i;
	size_t			size;

	i = 0;
	size = sizeof(pthread_mutex_t) * number_of_philosophers;
	forks = (pthread_mutex_t *)malloc(size);
	if (!forks)
		return (NULL);
	while (i < number_of_philosophers)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

void	assign_forks(t_philo *philos, pthread_mutex_t *forks,
			int number_of_philosophers)
{
	int	i;

	i = 0;
	while (i < number_of_philosophers)
	{
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % number_of_philosophers];
		i++;
	}
}
