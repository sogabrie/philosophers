/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:39:22 by sogabrie          #+#    #+#             */
/*   Updated: 2023/03/19 19:09:26 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


size_t	get_time_mls(void)
{
	struct timeval	a;
	size_t			time;

	gettimeofday(&a, NULL);
	time = a.tv_sec * 1000;
	time += a.tv_usec / 1000;
	return (time);
}

void	*check_died(void *pt)
{
	t_philo *philo;
	
	philo = (t_philo *)pt;
	//printf("=========================================================== id = %zu\n", philo->ip_philo);
	while (1)
	{
		//printf("time_philo = %zu philo_time_to_die = %zu get_time = %zu\n", philo->time_philo, philo->time_to_die, get_time_mls());
		//printf("start tim = %zu philo tim = %zu\n", philo->my_mut->start_time, philo->time_philo);
		if (philo_die(philo))
		{
			//printf("dies_5\n");
			do_philo(philo, 5);
			sem_post(philo->my_mut->flag_dead);
			break ;
		}
	}
	return (0);
}

int	philo_die(t_philo *philo)
{
	//printf("time_philo = %zu philo_time_to_die = %zu get_time = %zu\n", philo->time_philo, philo->time_to_die, get_time_mls());
	if (philo->time_philo + philo->time_to_die < get_time_mls())
	{
		//printf("time_philo = %zu philo_time_to_die = %zu get_time = %zu\n", philo->time_philo, philo->time_to_die, get_time_mls());
		return (1);
	}
	return (0);
}

void	do_philo(t_philo *philo, size_t i)
{
	//printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< id = %zu i = %zu \n", philo->ip_philo, i);
	sem_wait(philo->my_mut->flag_print);
	if (i == 1)
		printf("%zu %zu has taken a fork\n", get_time_mls() \
				- philo->start_time, philo->ip_philo);
	else if (i == 2)
		printf("%zu %zu is eating\n", get_time_mls() - \
				philo->start_time, philo->ip_philo);
	else if (i == 3)
		printf("%zu %zu is sleeping\n", get_time_mls() - \
				philo->start_time, philo->ip_philo);
	else if (i == 4)
		printf("%zu %zu is thinking\n", get_time_mls() - \
				philo->start_time, philo->ip_philo);
	else if (i == 5)
	{
		printf("%zu %zu died\n", get_time_mls() - \
				philo->start_time, philo->ip_philo);
	}
	if (i != 5)
	{
		//printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> id = %zu i = %zu\n", philo->ip_philo, i);
		sem_post(philo->my_mut->flag_print);
	}
}
