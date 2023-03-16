#include "philosophers.h"

void	*sleep_died(void *ph)
{
	usleep(500);
	exit(0);
	return (NULL);
}