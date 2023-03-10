#include "philosophers.h"

void	*my_thread(void *ph)
{
	t_philo *philo;

	philo = (t_philo *)ph;
	printf("philo count = %zu \n",philo->count);
	printf("philo ip_philo = %zu \n",philo->ip_philo);
	printf("philo time_to_die = %zu \n",philo->time_to_die);
	printf("philo time_to_eat = %zu \n",philo->time_to_eat);
	printf("philo time_sleep = %zu \n",philo->time_sleep);
	printf("philo count_each_philo = %zu \n",philo->count_each_philo);
	printf("philo flag_count_each_philo = %zu \n", philo->flag_count_each_philo);
	printf("\n");
	return (0);
}

int	start(t_philo **philo, size_t count, size_t i)
{
	while (i < count)
	{
		//printf("start i = %zu count = %zu\n", i, count);
		pthread_create(&(philo[i]->my_thread), NULL, my_thread, philo[i]);
		++i;
	}
	i = 0;
	while(i < count)
	{
		pthread_join(philo[i]->my_thread, NULL);
		printf("END thread -> %zu\n", philo[i]->ip_philo);
		++i;
	}
	return (0);
}