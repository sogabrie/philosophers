/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 19:49:24 by sogabrie          #+#    #+#             */
/*   Updated: 2023/03/19 19:53:35 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	cheack_eat_philo(t_philo *philo)
{
	sem_wait(philo->my_mut->fork);
	do_philo(philo, 1);
	sem_wait(philo->my_mut->fork);
	do_philo(philo, 1);
	philo->time_philo = get_time_mls();
}

void	cheack_eat_philo_2(t_philo *philo)
{
	do_philo(philo, 2);
	usleep(philo->time_to_eat * 1000);
	sem_post(philo->my_mut->fork);
	sem_post(philo->my_mut->fork);
	do_philo(philo, 3);
	usleep(philo->time_sleep * 1000);
}

void	time_philo(t_philo *philo)
{
	cheack_eat_philo(philo);
	cheack_eat_philo_2(philo);
	do_philo(philo, 4);
	if (philo->flag_count_each_philo)
	{
		--philo->count_each_philo;
		if (!philo->count_each_philo)
			exit(0);
	}
}

void	my_thread(t_philo *philo)
{
	pthread_t	tr;

	philo->time_philo = get_time_mls();
	philo->start_time = get_time_mls();
	pthread_create(&tr, NULL, check_died, philo);
	pthread_detach(tr);
	while (1)
	{
		time_philo(philo);
	}
}

void	start(t_philo **philo, size_t count, size_t i)
{
	pthread_t	tr;

	philo[0]->flag_free = 0;
	while (i < count)
	{
		philo[i]->pid = fork();
		if (!philo[i]->pid)
		{
			my_thread(philo[i]);
			exit(0);
		}
		++i;
		usleep(1000);
	}
	pthread_create(&tr, NULL, cheack_free, philo);
	pthread_detach(tr);
	sem_wait(philo[0]->my_mut->flag_dead);
	philo[0]->flag_free = 1;
	i = 0;
	while (i < count)
	{
		kill(philo[i]->pid, SIGTERM);
		++i;
	}
}
