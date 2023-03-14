/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initalizatia_mut.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:38:59 by sogabrie          #+#    #+#             */
/*   Updated: 2023/03/14 16:21:43 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	initalizatia_mut(t_my_mutexs **my_mut, size_t size)
{
	size_t i;
	sem_t	*dead;

	i = 0;
	*my_mut = malloc(sizeof(t_my_mutexs));
	if (!*my_mut)
		return (2);
	(*my_mut)->fork = sem_open("/my_sem_", O_CREAT , 777, 1);
	(*my_mut)->flag_dead = sem_open("/sem_diad_", O_CREAT , 777, 1);
	while(i < size)
	{
		sem_post((*my_mut)->fork);
		++i;
	}
	//sem_post((*my_mut)->flag_dead);
	// (*my_mut)->flag_dead = sem_open("/sem_diad_", O_CREAT | O_EXCL , 777 );
	//printf("sem_pos = %d  dead = %d fork = %d dead = %d\n", sem_post((*my_mut)->flag_dead), (*my_mut)->flag_dead , (*my_mut)->fork, dead);
	return (0);
}
