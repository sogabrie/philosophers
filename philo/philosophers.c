#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_philo		philo[argc - 1];
	t_my_mutexs	my_mut[argc - 1];

	if (argc < 2)
		return (0);
	printf("OK\n");
	if (cheack_argv(--argc, ++argv))
		return (1);
	if (initalizatia_mut(&my_mut))
		return (2);
	philo->my_mut = &my_mut;
	if (inicalizatia_philo(&philo, argc, argv))
		return(3);
	if (start(&philo))
		return (4);
	delet_mut(&my_mut);
	return (0);
}