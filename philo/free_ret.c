#include "philosophers.h"

int	free_philo(t_philo ***phil, int size)
{
	size_t	i;

	//write(1, "free_philo\n", 12);
	i = 0;
	if (!*phil)
	{
		system("leaks pilo");
		return (1);
	}
	while (i < size)
	{
		free((*phil)[i]);
		++i;
	}
	free(*phil);
	system("leaks pilo");
	return (1);
}

int	free_mut(t_my_mutexs ***mut, int size)
{
	int	i;

	i = 0;
	if (!*mut)
	{
		system("leaks pilo");
		return (1);
	}
	while (i < size)
	{
		pthread_mutex_destroy(&(*mut)[i]->fork);
		free((*mut)[i]);
		++i;
	}
	free(*mut);
	system("leaks pilo");
	return (1);
}