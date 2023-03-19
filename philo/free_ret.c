/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ret.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:38:52 by sogabrie          #+#    #+#             */
/*   Updated: 2023/03/19 19:43:45 by sogabrie         ###   ########.fr       */
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

int	free_mut(t_my_mutexs ***mut, int size)
{
	int	i;

	i = 0;
	if (!*mut)
	{
		return (0);
	}
	while (i < size)
	{
		pthread_mutex_destroy(&(*mut)[i]->fork);
		free((*mut)[i]);
		++i;
	}
	free(*mut);
	return (0);
}
