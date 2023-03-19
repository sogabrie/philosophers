/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:39:30 by sogabrie          #+#    #+#             */
/*   Updated: 2023/03/19 19:10:20 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	cheack_eat_philo(t_philo *philo)
{
	// if (philo_die(philo))
	// 	return (print_died(philo));
	//printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& id = %zu\n", philo->ip_philo);
	sem_wait(philo->my_mut->fork);
	// printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ id = %zu\n", philo->ip_philo);
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
		// printf("philo->count_each_philo = %zu id = %zu\n",philo->count_each_philo, philo->ip_philo);
		--philo->count_each_philo;
		// printf("philo->count_each_philo = %zu id = %zu\n",philo->count_each_philo, philo->ip_philo);
		if (!philo->count_each_philo)
			exit(0);
	}
}

void	my_thread(t_philo *philo)
{
	pthread_t tr;

	//printf("=========================================================== id = %zu\n", philo->ip_philo);
	philo->time_philo = get_time_mls();
	//printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< id = %zu\n", philo->ip_philo);
	philo->start_time = get_time_mls();
	// printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> id = %zu\n", philo->ip_philo);
	// printf("count = %zu\n", philo->count);
	// printf("ip_philo  = %zu\n", philo->ip_philo);
	// printf("time_to_die = %zu\n", philo->time_to_die);
	// printf("time_to_eat = %zu\n", philo->time_to_eat);
	// printf("time_sleep = %zu\n", philo->time_sleep);
	// printf("count_each_philo = %zu\n", philo->count_each_philo);
	pthread_create(&tr, NULL, check_died, philo);
	pthread_detach(tr);
	// while (1)
	// {
	// 	philo->time_philo = get_time_mls();
	// 	philo->start_time = get_time_mls();
	// }
	while (1)
	{
		time_philo(philo);
	}
}

void	start(t_philo **philo, size_t count, size_t i)
{
	philo[0]->flag_free = 0;
	//philo[0]->my_mut->flag_dead = 0;
	//printf("count = %zu i = %zu\n", count, i);
	while (i < count)
	{
		//printf("-----------------------------------------+++++++++++++++++++philo -> %zu   count = %zu\n", i, count);
		philo[i]->pid = fork();
		// if (philo[i]->pid == -1)
		// {
		// 	exit(2);
		// }
		if (!philo[i]->pid)
		{
			//printf("-----------------------------------------philo -> %zu   count = %zu\n", i, count);
			my_thread(philo[i]);
			exit(0);
		}
		++i;
		usleep(1000);
	}
	//usleep(10000000);
	pthread_t tr;
	pthread_create(&tr, NULL, cheack_free, philo);
	pthread_detach(tr);
	// philo[0]->flag_free = 1;
	//usleep(10000000);
	//printf("start_9\n");
	sem_wait(philo[0]->my_mut->flag_dead);
	philo[0]->flag_free = 1;
	// printf("start_10\n");
	i = 0;
	while (i < count)
	{
		kill(philo[i]->pid, SIGTERM);
		++i;
	}
	//free_exit(&philo);
}
