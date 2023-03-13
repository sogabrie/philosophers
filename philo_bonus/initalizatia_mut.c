/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initalizatia_mut.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:38:59 by sogabrie          #+#    #+#             */
/*   Updated: 2023/03/13 18:39:22 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	initalizatia_mut(t_my_mutexs **my_mut, size_t size)
{
	size_t i;

	i = 0;
	*my_mut = malloc(sizeof(t_my_mutexs));
	if (!*my_mut)
		return (2);
	(*my_mut)->fork = sem_open("/my_sem_", O_CREAT | O_EXCL , 777 );
	while(i < size)
	{
		sem_post((*my_mut)->fork);
		++i;
	}
	return (0);
}
