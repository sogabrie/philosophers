/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:39:10 by sogabrie          #+#    #+#             */
/*   Updated: 2023/03/13 22:04:22 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	size_t		mas[5];
	size_t		i;
	t_philo		**philo;
	t_my_mutexs	**my_mut;

	i = -1;
	if (argc < 5 || argc > 6)
		return (printf("wrong number of arguments or wrong arguments\n"));
	if (cheack_inic_argv(&philo, --argc, ++argv, mas))
		return (free_philo(&philo, mas[0]) || \
		printf("wrong number of arguments or wrong arguments\n"));
	if (initalizatia_mut(&my_mut, mas[0], 0, 0))
		return (free_philo(&philo, mas[0]) || free_mut(&my_mut, mas[0]));
	while (++i < philo[0]->count)
		philo[i]->my_mut = my_mut;
	start(philo, mas[0], 0);
	free_mut(&my_mut, mas[0]);
	free_philo(&philo, mas[0]);
	//system("leaks pilo");
	return (0);
}
