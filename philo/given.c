/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   given.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:28:52 by yhusieva          #+#    #+#             */
/*   Updated: 2025/02/23 20:42:52 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	init_mutexes(t_given *given_params)
{
	pthread_mutex_init(&given_params->print_mutex, NULL);
	pthread_mutex_init(&given_params->time_mutex, NULL);
	pthread_mutex_init(&given_params->eating_mutex, NULL);
	pthread_mutex_init(&given_params->end_mutex, NULL);
}

int	initialise_params(t_given *given_params, int argc, char *argv[])
{
	given_params->number_of_philosophers = ft_atoi(argv[1]);
	given_params->time_to_die = ft_atoi(argv[2]);
	given_params->time_to_eat = ft_atoi(argv[3]);
	given_params->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		given_params->meal_goal = ft_atoi(argv[5]);
	else
		given_params->meal_goal = INT_MAX;
	if (given_params->number_of_philosophers <= 0)
	{
		printf("Imagine negative (zero) units of people.\n");
		return (1);
	}
	if (given_params->time_to_die <= 0 || given_params->time_to_eat <= 0
		|| given_params->time_to_sleep <= 0 || given_params->meal_goal <= 0)
	{
		printf("Good luck with the time travel to the past.\n");
		return (1);
	}
	given_params->end_flag = 0;
	given_params->start_time = gettime();
	init_mutexes(given_params);
	return (0);
}
