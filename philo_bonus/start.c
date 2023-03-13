/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:39:30 by sogabrie          #+#    #+#             */
/*   Updated: 2023/03/13 17:32:09 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	cheack_eat_philo(t_philo *philo)
{
	printf("eat_3\n");
// 	while (philo->my_mut->flag_fork < 2)
// 	{
// //		printf("%zu %zu       flag fork = %d\n",  get_time_mls() - philo->my_mut->start_time, philo->ip_philo, philo->my_mut->flag_fork);
// 		if (philo_die(philo))
// 			return (print_died(philo));
// 	}
	//printf("%zu %zu       flag fork = %d\n",  get_time_mls() - philo->my_mut->start_time, philo->ip_philo, philo->my_mut->flag_fork);
	philo->my_mut->fork = sem_open("/my_sem", O_CREAT | O_EXCL);
	printf("%zu %zu       sem_wait = %d\n",  get_time_mls() - philo->my_mut->start_time, philo->ip_philo, philo->my_mut->fork);
	while (sem_wait(philo->my_mut->fork) == -1)
	{
		//printf("%zu %zu       flag fork = %d\n",  get_time_mls() - philo->my_mut->start_time, philo->ip_philo, philo->my_mut->flag_fork);
		if (philo_die(philo))
			return (print_died(philo));
	}
	printf("eat_4\n");
	if (philo_die(philo) || philo->count == 1)
		return (print_died(philo));
	while (sem_wait(philo->my_mut->fork) == -1)
	{
		if (philo_die(philo))
			return (print_died(philo));
	}
	if (philo_die(philo) || philo->count == 1)
		return (print_died(philo));
	// philo->my_mut->flag_fork -= 2;
	do_philo(philo, 1);
	//do_philo(philo, 1);
	// sem_wait(philo->my_mut->fork);
	// sem_wait(philo->my_mut->fork);
	philo->time_philo = get_time_mls();
	do_philo(philo, 2);
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
	//philo->my_mut->flag_fork += 2;
	sem_close(philo->my_mut->fork);
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
	if (cheack_eat_philo(philo))
		return (1);
	if (cheack_eat_philo_2(philo, &f))
		return (1);
	if (philo_die(philo))
		return (print_died(philo));
	do_philo(philo, 4);
	if (philo->flag_count_each_philo)
	{
		--philo->count_each_philo;
		if (!philo->count_each_philo)
			return (2);
	}
	return (0);
}

void	my_thread(t_philo	*philo)
{
	size_t	i;

	i = 0;
	philo->time_philo = get_time_mls();
	if (!philo->my_mut->start_time)
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
			//printf("start i = %zu\n", i);
			my_thread(philo[i]);
			exit(0);
		}
		++i;
	}
	i = 0;
	while (i < count)
	{
		//printf("END i = %zu\n", i);
		waitpid(philo[i]->pid, NULL, 0);
		++i;
	}
	return (0);
}
