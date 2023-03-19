/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initalizatia_mut.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 19:48:59 by sogabrie          #+#    #+#             */
/*   Updated: 2023/03/19 19:51:15 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	initalizatia_mut(t_my_mutexs *my_mut, size_t size)
{
	sem_unlink("/my_sem_");
	sem_unlink("/sem_diad_");
	sem_unlink("/sem_print_");
	(*my_mut).fork = sem_open("/my_sem_", O_CREAT, 600, size);
	(*my_mut).flag_dead = sem_open("/sem_diad_", O_CREAT, 600, 0);
	(*my_mut).flag_print = sem_open("/sem_print_", O_CREAT, 600, 1);
	return (0);
}
