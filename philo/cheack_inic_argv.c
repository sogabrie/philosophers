#include "philosophers.h"

long	ft_atoi(const char *nptr)
{
	long	i;
	long	f;
	long	ptr;

	i = 0;
	f = 0;
	ptr = 0;
	while (nptr[i] != 0 && (nptr[i] == ' '))
		++i;
	if (nptr[i] != 0 && nptr[i] == '-')
	{
		++i;
		f = 1;
	}
	else if (nptr[i] != 0 && nptr[i] == '+')
		++i;
	while (nptr[i] != 0 && ft_isdigit(nptr[i]))
		ptr = (10 * ptr) + (nptr[i++] - 48);
	if (f == 1)
		return (-ptr);
	return (ptr);
}

int	cheack_argv(size_t	*mas, int argc, char **argv)
{
	size_t		i;
	long 		lo;

	i = 0;
	if (argc < 5)
		mas[4] = 0;
	while (i < argc)
	{
		if (chack_number(argv[i]))
			return (1);
		if (ft_strlen_zero(argv[i], 0, 0, 0) > 15)
			return (1);
		lo = ft_atoi(argv[i]);
		if (lo > 4294967295 || lo < 0)
			return (1);
		(mas)[i++] = (size_t)lo;
	}
	return (0);
}

int	malloc_philo(t_philo ***philo, size_t *mas, int i, int f)
{
	//printf("mas[o] = %zu 1 = %zu 2 = %zu 3 = %zu 4 = %zu\n", mas[0], mas[1], mas[2], mas[3], mas[4]);
	while (i < mas[0])
	{
		(*philo)[i] = malloc(sizeof(t_philo));
		if (!(*philo)[i])
			f = 1;
		else
		{
			(*philo)[i]->count = mas[0];
			(*philo)[i]->my_mut = 0;
			(*philo)[i]->ip_philo = i + 1;
			(*philo)[i]->time_to_die = mas[1];
			(*philo)[i]->time_to_eat = mas[2];
			(*philo)[i]->time_sleep = mas[3];
			(*philo)[i]->count_each_philo = mas[4];
		}
		++i;

	}
	if (f)
		return (2);
	return (0);
}

int cheack_inic_argv(t_philo ***philo, int argc, char **argv)
{
	size_t	mas[5];
	int		i;

	i = 0;
	if (cheack_argv(mas, argc, argv))
		return (1);
	*philo = malloc(mas[0] * sizeof(t_philo *));
	if (!philo)
		return (2);
	if (malloc_philo(philo, mas, 0, 0))
		return (2);
	while (i < mas[0])
	{
		if (argc == 5)
			(*philo)[i]->flag_count_each_philo = 1;
		else
			(*philo)[i]->flag_count_each_philo = 0;
		++i;
	}
	return (0);
}