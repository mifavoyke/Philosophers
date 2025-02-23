/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:24:31 by yhusieva          #+#    #+#             */
/*   Updated: 2025/02/23 20:59:39 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int validate_input(int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_number(argv[i]))
		{
			printf("Numeric values are expected.\n");
			return (1);
		}
		i++;
	}
	return (0);
}

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
	create_philo(&philos, &forks, &given_params);
	cleanup(philos, forks);
	return (0);
}
