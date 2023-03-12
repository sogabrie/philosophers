/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:39:10 by sogabrie          #+#    #+#             */
/*   Updated: 2023/03/13 00:08:59 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_filo(t_philo **philo)
{
	int i = 0;
	while (i < philo[0]->count)
	{
		printf("philo count = %zu \n",philo[i]->count);
		printf("philo ip_philo = %zu \n",philo[i]->ip_philo);
		printf("philo time_to_die = %zu \n",philo[i]->time_to_die);
		printf("philo time_to_eat = %zu \n",philo[i]->time_to_eat);
		printf("philo time_sleep = %zu \n",philo[i]->time_sleep);
		printf("philo count_each_philo = %zu \n",philo[i]->count_each_philo);
		printf("philo flag_count_each_philo = %zu \n", philo[i]->flag_count_each_philo);
		printf("\n");
		++i;
	}
}

int	main(int argc, char **argv)
{
	size_t		mas[5];
	size_t		i;
	t_philo		**philo;
	t_my_mutexs	*my_mut;

	i = -1;
	if (argc < 5 || argc > 6)
		return (0);
	if (cheack_inic_argv(&philo, --argc, ++argv, mas))
		return (free_philo(&philo, mas[0]));
	if (initalizatia_mut(&my_mut, mas[0]))
		return (free_philo(&philo, mas[0]) || free_mut(&my_mut));
	while (++i < philo[0]->count)
		philo[i]->my_mut = my_mut;
	start(philo, mas[0], 0);
	free_mut(&my_mut);
	free_philo(&philo, mas[0]);
	//system("leaks pilo");
	return (0);
}
