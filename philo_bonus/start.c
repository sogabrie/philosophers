/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:39:30 by sogabrie          #+#    #+#             */
/*   Updated: 2023/03/16 22:56:20 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
