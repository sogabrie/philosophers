/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:39:30 by sogabrie          #+#    #+#             */
/*   Updated: 2023/03/17 20:06:06 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	cheack_eat_philo(t_philo *philo)
{
	// if (philo_die(philo))
	// 	return (print_died(philo));
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
	// while (get_time_mls() < philo->time_philo + philo->time_to_eat && !*f)
	// {
	// 	if (philo_die(philo))
	// 		*f = 1;
	// }
	sem_post(philo->my_mut->fork);
	sem_post(philo->my_mut->fork);
	// if (*f)
	// 	return (print_died(philo));
	do_philo(philo, 3);
	usleep(philo->time_sleep * 1000);
	// *f = get_time_mls();
	// while (get_time_mls() < (*f + philo->time_sleep))
	// {
	// 	if (philo_die(philo))
	// 		return (print_died(philo));
	// }
}

void	time_philo(t_philo *philo)
{
	cheack_eat_philo(philo);
	cheack_eat_philo_2(philo);
	// if (philo_die(philo))
	// 	return (print_died(philo));
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
	pthread_t tr;

	philo->time_philo = get_time_mls();
	if (!philo->my_mut->start_time)
		philo->my_mut->start_time = get_time_mls();
	pthread_create(&tr, NULL, check_died, philo);
	pthread_detach(tr);
	while (1)
	{
		time_philo(philo);
	}
}

int	start(t_philo **philo, size_t count, size_t i)
{
	philo[0]->my_mut->start_time = 0;
	philo[0]->my_mut->flag_dead = 0;
	while (i < count)
	{
		philo[i]->pid = fork();
		if (philo[i]->pid == -1)
		{
			exit(2);
		}
		if (!philo[i]->pid)
		{
			my_thread(philo[i]);
			exit(0);
		}
		++i;
	}
	sem_wait(philo[0]->my_mut->flag_dead);
	printf("start_10\n");
	i = 0;
	while (i < count)
	{
		kill(philo[i]->pid, SIGTERM);
		++i;
	}
	return (0);
}
