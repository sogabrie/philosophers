/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:39:22 by sogabrie          #+#    #+#             */
/*   Updated: 2023/03/13 22:05:53 by sogabrie         ###   ########.fr       */
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

int	philo_die(t_philo *philo)
{
	if (philo->time_philo + philo->time_to_die < get_time_mls())
	{
		return (1);
	}
	return (0);
}

int	print_died(t_philo *philo)
{
	usleep(100);
	if (!philo->my_mut[0]->flag_dead)
	{
		philo->my_mut[0]->flag_dead = 1;
		printf("%zu %zu died\n", get_time_mls() - \
		philo->my_mut[0]->start_time, philo->ip_philo);
	}
	return (1);
}

void	do_philo(t_philo *philo, size_t i)
{
	usleep(500);
	while (philo->my_mut[0]->flag_dead)
	{
		if (philo_die(philo))
		{
			(print_died(philo));
			return ;
		}
	}
	if (!philo->my_mut[0]->flag_dead)
	{
		if (i == 1)
			printf("%zu %zu has taken a fork\n", get_time_mls() \
					- philo->my_mut[0]->start_time, philo->ip_philo);
		else if (i == 2)
			printf("%zu %zu is eating\n", get_time_mls() - \
					philo->my_mut[0]->start_time, philo->ip_philo);
		else if (i == 3)
			printf("%zu %zu is sleeping\n", get_time_mls() - \
					philo->my_mut[0]->start_time, philo->ip_philo);
		else if (i == 4)
			printf("%zu %zu is thinking\n", get_time_mls() - \
					philo->my_mut[0]->start_time, philo->ip_philo);
	}
}
