/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:10:03 by yhusieva          #+#    #+#             */
/*   Updated: 2025/02/25 20:14:48 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_given
{
	int				number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				meal_goal;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	time_mutex;
	pthread_mutex_t	eating_mutex;
	pthread_mutex_t	end_mutex;
	int				end_flag;
	pthread_t		supervisor_thread;
	long			start_time;
}	t_given;

typedef struct s_philo
{
	pthread_t		philosopher;
	int				id;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	long			last_meal_time;
	int				meals_eaten;
	t_given			*given_params;
}	t_philo;

// MAIN
int				create_philo(t_philo **philos, pthread_mutex_t **forks,
					t_given *given_params);
int				ft_eating(t_philo *philo);
void			*routine(void *arg);
void			*supervise(void *arg);
pthread_mutex_t	*initialise_forks(int number_of_philosophers);
void			assign_forks(t_philo *philos, pthread_mutex_t *forks,
					int number_of_philosophers);
int				initialise_params(t_given *given_params,
					int argc, char *argv[]);
int				check_end(t_philo *philo);

// UTILS
void			cleanup(t_philo *philos, pthread_mutex_t *forks);
long			gettime(void);
long			format_time(long start_time);
void			print_log(t_philo *philos, char *msg, char *colour);
int				ft_atoi(const char *nptr);
int				is_number(const char *str);
int				validate_input(int argc, char *argv[]);

#endif