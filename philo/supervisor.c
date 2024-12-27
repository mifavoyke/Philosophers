#include "../include/philo.h"

void *supervise(void *arg)
{
	t_philo *philos;
	unsigned long death_time;
	unsigned int i;

	philos = (t_philo *)arg;

	while (1)
	{
		i = 0;
		while (i < philos[0].given_params->number_of_philosophers)
		{
			death_time = philos[i].last_meal_time + philos[i].given_params->time_to_die;
			if (death_time <= gettime())
			{
				printf("%ld %d died\n", gettime(), philos[i].id);
				i = 0;
				while (i < philos[0].given_params->number_of_philosophers)
				{
					pthread_detach(philos[i].philosopher);
					i++;
				}
				return (NULL);
			}
			i++;
		}
		usleep(10 * 1000);
	}
	return (NULL);
}