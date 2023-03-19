/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ret.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 19:48:53 by sogabrie          #+#    #+#             */
/*   Updated: 2023/03/19 19:54:37 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	free_philo(t_philo ***phil, int size)
{
	int	i;

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
	sem_close(((*mut).fork));
	sem_close(((*mut).flag_dead));
	sem_close(((*mut).flag_print));
	sem_unlink("/my_sem_");
	sem_unlink("/sem_diad_");
	sem_unlink("/sem_print_");
	return (0);
}

void	*cheack_free(void *pt)
{
	size_t	i;
	t_philo	**philo;

	philo = ((t_philo **)pt);
	i = 0;
	while (i < philo[0]->count)
	{
		waitpid(philo[i]->pid, NULL, 0);
		++i;
	}
	if (!philo[0]->flag_free)
	{
		sem_post(philo[0]->my_mut->flag_dead);
	}
	return (NULL);
}
