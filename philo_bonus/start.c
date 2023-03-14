/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:39:30 by sogabrie          #+#    #+#             */
/*   Updated: 2023/03/14 17:52:49 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	cheack_eat_philo(t_philo *philo)
{
	pthread_t dead;
	printf("eat_phio_1_0 = %zu\n" , philo->ip_philo);
	
	sem_wait(philo->my_mut->fork);
	//printf("eat_phio_1_1 = %zu\n" , philo->ip_philo);
	if (philo_die(philo))
		return (print_died(philo));
	//printf("eat_phio_1_2 = %zu\n" , philo->ip_philo);
	
	sem_wait(philo->my_mut->fork);
	//printf("eat_phio_1_3 = %zu\n" , philo->ip_philo);
	if (philo_die(philo))
		return (print_died(philo));
	//printf("eat_phio_1_4 = %zu\n" , philo->ip_philo);
	do_philo(philo, 1);
	//printf("eat_phio_1_5 = %zu\n" , philo->ip_philo);
	philo->time_philo = get_time_mls();
	//printf("eat_phio_1_6 = %zu\n" , philo->ip_philo);
	do_philo(philo, 2);
	//printf("eat_phio_1_7 = %zu\n" , philo->ip_philo);
	return (0);
}

int	cheack_eat_philo_2(t_philo *philo, size_t *f)
{
	*f = 0;
	while (get_time_mls() < philo->time_philo + philo->time_to_eat && !*f)
	{
		if (philo_die(philo))
			*f = 1;
	}
	sem_post(philo->my_mut->fork);
	sem_post(philo->my_mut->fork);
	if (*f)
		return (print_died(philo));
	do_philo(philo, 3);
	*f = get_time_mls();
	while (get_time_mls() < (*f + philo->time_sleep))
	{
		if (philo_die(philo))
			return (print_died(philo));
	}
	return (0);
}

size_t	time_philo(t_philo *philo, size_t f)
{
	printf("time_philo_0 = %zu\n" , philo->ip_philo);
	if (cheack_eat_philo(philo))
		return (1);
	printf("time_philo_1 = %zu\n" , philo->ip_philo);
	if (cheack_eat_philo_2(philo, &f))
		return (1);
	printf("time_philo_2 = %zu\n" , philo->ip_philo);
	if (philo_die(philo))
		return (print_died(philo));
	printf("time_philo_3 = %zu\n" , philo->ip_philo);
	do_philo(philo, 4);
	printf("time_philo_4 = %zu\n" , philo->ip_philo);
	if (philo->flag_count_each_philo)
	{
		printf("time_philo_5 = %zu\n" , philo->ip_philo);
		--philo->count_each_philo;
		if (!philo->count_each_philo)
			return (2);
		printf("time_philo_6 = %zu\n" , philo->ip_philo);
	}
	printf("time_philo_7 = %zu\n" , philo->ip_philo);
	return (0);
}

void	my_thread(t_philo	*philo)
{
	size_t	i;

	i = 0;
	philo->time_philo = get_time_mls();
	philo->my_mut->start_time = get_time_mls();
	while (!i)
	{
		i = time_philo(philo, 0);
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
	i = 0;
	while (i < count)
	{
		waitpid(philo[i]->pid, NULL, 0);
		++i;
	}
	return (0);
}
