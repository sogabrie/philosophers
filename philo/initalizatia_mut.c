#include "philosophers.h"

int	creat_mut(t_my_mutexs ***my_mut, size_t size, size_t i, size_t f)
{
	//printf("aaaaaaaa\n");
	while (i < size)
	{
		f = pthread_mutex_init(&(*my_mut)[i]->fork, NULL);
		(*my_mut)[i++]->flag_fork = 0;
	}
	if (f)
		return (3);
	return (0);
}

int	initalizatia_mut(t_my_mutexs ***my_mut, size_t size, size_t i, size_t f)
{
	*my_mut = malloc(size * (sizeof(t_my_mutexs *)));
	if (!*my_mut)
		return (2);
	while (i < size)
	{
		(*my_mut)[i] = malloc (sizeof(t_my_mutexs));
		if (!(*my_mut)[i])
			f = 1;
		++i;
	}
	if (f)
		return (2);
	return (creat_mut(my_mut, size, 0, 0));
}