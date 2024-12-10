#include "../include/philo.h"

unsigned long update_death_note(t_philo *philo)
{
	return (philo->last_meal_time + philo->given_params->time_to_die);
}

int *supervise(void *arg)
{
	t_philo **philos;
	unsigned long death_time;
	int i = 0;

	philos = (t_philo **)arg;

	while (philos[i])
	{
		death_time = update_death_note(philos[i]);
		if (death_time == gettime())
		{
			while (philos[i])
			{
				pthread_detach(philos[i]->philosopher);
				i++;
			}
			return (NULL);
		}
	}
}