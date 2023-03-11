#include "philosophers.h"

int	philo_die(t_philo *philo)
{
	if (philo->time_philo + philo->time_to_die > get_time_mls())
	{
		printf("dit\n");
		return (1);
	}
	return (0);
}

size_t	get_time_mls()
{
	struct timeval	a;
	size_t			time;

	gettimeofday(&a, NULL);
	//printf("sec = %zu usec = %d\n", a.tv_sec, a.tv_usec);
	time = a.tv_sec * 1000;
	time += a.tv_usec / 1000;
	//printf("time = %zu\n", time);
	return (time);
}