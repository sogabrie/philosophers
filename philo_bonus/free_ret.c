/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ret.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:38:52 by sogabrie          #+#    #+#             */
/*   Updated: 2023/03/17 17:10:06 by sogabrie         ###   ########.fr       */
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

int	free_mut(t_my_mutexs **mut)
{
	int	i;

	if (!*mut)
		return (0);
	sem_close(((*mut)->fork));
	sem_close(((*mut)->flag_dead));
	sem_close(((*mut)->flag_print));
	sem_unlink("/my_sem_");
	sem_unlink("/sem_diad_");
	sem_unlink("/sem_print_");
	free(*mut);
	return (0);
}
