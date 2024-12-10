#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <stdbool.h>

typedef struct s_given
{
	unsigned int number_of_philosophers;
	unsigned long time_to_die;
	unsigned long time_to_eat;
	unsigned long time_to_sleep;
	unsigned int number_of_times_each_philosopher_must_eat;
	pthread_mutex_t print_mutex;
	pthread_t supervisor_thread;
} t_given;

typedef struct s_philo
{
	pthread_t philosopher;
	unsigned int id;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *left_fork;
	unsigned long last_meal_time;
	unsigned int number_of_meals_eaten;
	t_given *given_params;
} t_philo;

// MAIN
void ft_create_philo(t_philo **philos, pthread_mutex_t **forks, t_given *given_params);
void *ft_routine(void *arg);
int *supervise(void *arg);
pthread_mutex_t *initialise_forks(unsigned int number_of_philosophers);
void assign_forks(t_philo *philos, pthread_mutex_t *forks, unsigned int number_of_philosophers);
// UTILS
void initialise_params(t_given *given_params, int argc, char *argv[]);
void ft_cleanup(t_philo *philos, pthread_mutex_t *forks);
unsigned long gettime();

/*
pthread_mutex_lock(philo->right_fork);
if (pthread_mutex_trylock(philo->left_fork) != 0)
{
	pthread_mutex_unlock(philo->right_fork);  // Release right fork if left not available
	return;
}
*/

#endif