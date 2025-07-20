/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:24:31 by yhusieva          #+#    #+#             */
/*   Updated: 2025/02/25 20:14:57 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char *argv[])
{
	t_given			given_params;
	t_philo			*philos;
	pthread_mutex_t	*forks;

	philos = NULL;
	forks = NULL;
	if (argc < 5)
	{
		printf("Invalid input. Expected format: ");
		printf("number_of_philos time_to_die eat sleep [meal_goal]\n");
		return (1);
	}
	if (validate_input(argc, argv))
		return (1);
	if (initialise_params(&given_params, argc, argv))
		return (1);
	if (create_philo(&philos, &forks, &given_params))
		return (1);
	cleanup(philos, forks);
	return (0);
}
