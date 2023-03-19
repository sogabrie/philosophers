/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ret.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:38:52 by sogabrie          #+#    #+#             */
/*   Updated: 2023/03/19 18:40:16 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	free_philo(t_philo ***phil, int size)
{
	size_t	i;

	i = 0;
	if (!*phil)
	{
		return (0);
	}
	while (i < size)
	{
		free((*phil)[i]);
		++i;
	}
	free(*phil);
	return (0);
}

int	free_mut(t_my_mutexs *mut)
{
	int	i;

	// if (!*mut)
	// 	return (0);
	sem_close(((*mut).fork));
	sem_close(((*mut).flag_dead));
	sem_close(((*mut).flag_print));
	sem_unlink("/my_sem_");
	sem_unlink("/sem_diad_");
	sem_unlink("/sem_print_");
	//free(*mut);
	return (0);
}

void	free_exit(t_philo ***phil)
{
	printf("free_exit_0\n");
	free_mut((*phil)[0]->my_mut);
	free_philo(phil, (*phil)[0]->count);
	exit(0);
}

void	*cheack_free(void *pt)
{
	size_t	i;
	t_philo **philo;
	
	philo = ((t_philo **)pt);
	i = 0;
	// printf("cheack_free_5\n");
	// printf("count = %zu free = %zu \n", (philo[0]->count), philo[0]->flag_free);
	while (i < philo[0]->count)
	{
		// printf("cheack_free_6\n");
		waitpid(philo[i]->pid, NULL, 0);
		++i;
	}
	// printf("cheack_free_10\n");
	printf("count = %zu free = %zu \n", (philo[0]->count), philo[0]->flag_free);
	if (!philo[0]->flag_free)
	{
		// free_exit(&philo);
		sem_post(philo[0]->my_mut->flag_dead);
	}
	return (NULL);
}