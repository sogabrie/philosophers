/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:39:22 by sogabrie          #+#    #+#             */
/*   Updated: 2023/03/16 16:26:55 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*chech_diad(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	while (1)
	{

		if (philo_die(philo))
		{
			//printf("chech_diad_5\n");
			print_died(philo);
			printf("chech_diad_6\n");
			exit(0);
		}
	}
	return (NULL);
}

size_t	get_time_mls(void)
{
	struct timeval	a;
	size_t			time;

	gettimeofday(&a, NULL);
	time = a.tv_sec * 1000;
	time += a.tv_usec / 1000;
	return (time);
}

int	print_died(t_philo *philo)
{
	pthread_t dead;
	
	pthread_create(&dead, NULL, sleep_died, NULL);
	sem_wait(philo->my_mut->flag_dead);
	pthread_detach(dead);
	printf("%zu %zu died\n",  get_time_mls() - philo->my_mut->start_time, philo->ip_philo);
	exit (0);
	return (1);
}

int	do_philo(t_philo *philo, size_t i)
{
	pthread_t dead;
	
	printf("%zu %zu                       time   \n",  get_time_mls() - philo->my_mut->start_time, philo->ip_philo);
	pthread_create(&dead, NULL, chech_diad, philo);
	sem_wait(philo->my_mut->flag_dead);
	pthread_detach(dead);
	if (i == 1)
		printf("%zu %zu has taken a fork\n",  get_time_mls() - philo->my_mut->start_time, philo->ip_philo);
	else if (i == 2)
		printf("%zu %zu is eating\n",  get_time_mls() - philo->my_mut->start_time, philo->ip_philo);
	else if (i == 3)
		printf("%zu %zu is sleeping\n",  get_time_mls() - philo->my_mut->start_time, philo->ip_philo);
	else if (i == 4)
		printf("%zu %zu is thinking\n",  get_time_mls() - philo->my_mut->start_time, philo->ip_philo);
	sem_post(philo->my_mut->flag_dead);
	return (0);
}

int	philo_die(t_philo *philo)
{	
	if (philo->time_philo + philo->time_to_die < get_time_mls())
	{
		return (1);
	}
	return (0);
}
