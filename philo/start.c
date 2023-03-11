#include "philosophers.h"

int	cheack_eat_philo(t_philo *philo, size_t *i, size_t *i2)
{
	if (philo->ip_philo == philo->count)
		*i = 0;
	else
		*i = philo->ip_philo;
	*i2 = philo->ip_philo - 1;
	while(philo->count != 1 && (philo->my_mut[*i]->flag_fork != 0 || philo->my_mut[*i2]->flag_fork != 0))
	{
		if (philo_die(philo))
			return (1);
	}
	if (philo_die(philo))
		return (1);
	philo->my_mut[*i]->flag_fork = 1;
	philo->my_mut[*i2]->flag_fork = 1;
	printf("go fork\n");
	pthread_mutex_lock(&philo->my_mut[*i]->fork);
	pthread_mutex_lock(&philo->my_mut[*i2]->fork);
	philo->time_philo = get_time_mls();
	printf("go eat\n");
	return (0);
}

int	cheack_eat_philo_2(t_philo *philo, size_t *i, size_t *i2, size_t *f)
{
	while(get_time_mls() < philo->time_philo + philo->time_to_eat)
	{
		if (philo_die(philo))
			return (1);
	}
	pthread_mutex_unlock(&philo->my_mut[*i]->fork);
	pthread_mutex_unlock(&philo->my_mut[*i2]->fork);
	philo->my_mut[*i]->flag_fork = 0;
	philo->my_mut[*i2]->flag_fork = 0;
	printf("go sleep\n");
	*f = get_time_mls();
	while(get_time_mls() < *f + philo->time_sleep)
	{
		if (philo_die(philo))
			return (1);
	}
	return (0);
}

size_t time_philo(t_philo *philo, size_t i, size_t i2, size_t f)
{
	if (cheack_eat_philo(philo, &i, &i2))
		return (1);
	if (cheack_eat_philo_2(philo, &i, &i2, &f))
		return (1);
	if (philo_die(philo))
		return (1);
	printf("go thinking\n");
	if (philo->flag_count_each_philo)
	{
		--philo->count_each_philo;
		if (!philo->count_each_philo)
			return (2);
	}
	return (0);
}

void	*my_thread(void *ph)
{
	t_philo *philo;
	size_t		i;

	i = 0;
	philo = (t_philo *)ph;

	philo->time_philo = get_time_mls();
	// printf("philo time = %zu \n",philo->time_philo);
	// printf("philo count = %zu \n",philo->count);
	// printf("philo ip_philo = %zu \n",philo->ip_philo);
	// printf("philo time_to_die = %zu \n",philo->time_to_die);
	// printf("philo time_to_eat = %zu \n",philo->time_to_eat);
	// printf("philo time_sleep = %zu \n",philo->time_sleep);
	// printf("philo count_each_philo = %zu \n",philo->count_each_philo);
	// printf("philo flag_count_each_philo = %zu \n", philo->flag_count_each_philo);
	// printf("\n");

	while (!i)
	{
		i = time_philo(philo, 0, 0, 0);	
	}
	return (0);
}

int	start(t_philo **philo, size_t count, size_t i)
{
	while (i < count)
	{
		//printf("start i = %zu count = %zu\n", i, count);
		//usleep(5000);
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