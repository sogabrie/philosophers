/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:39:30 by sogabrie          #+#    #+#             */
/*   Updated: 2023/03/13 00:06:24 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	cheack_eat_philo(t_philo *philo, size_t *i, size_t *i2)
{
	if (philo->ip_philo == philo->count)
		*i = 0;
	else
		*i = philo->ip_philo;
	*i2 = philo->ip_philo - 1;
	while (philo->my_mut[*i]->flag_fork != 0 || \
		philo->my_mut[*i2]->flag_fork != 0)
	{
		if (philo_die(philo))
			return (print_died(philo));
	}
	if (philo_die(philo) || philo->count == 1)
		return (print_died(philo));
	philo->my_mut[*i]->flag_fork = 1;
	philo->my_mut[*i2]->flag_fork = 1;
	do_philo(philo, 1);
	//do_philo(philo, 1);
	pthread_mutex_lock(&philo->my_mut[*i]->fork);
	pthread_mutex_lock(&philo->my_mut[*i2]->fork);
	philo->time_philo = get_time_mls();
	do_philo(philo, 2);
	return (0);
}

int	cheack_eat_philo_2(t_philo *philo, size_t *i, size_t *i2, size_t *f)
{
	*f = 0;
	while (get_time_mls() < philo->time_philo + philo->time_to_eat && !*f)
	{
		if (philo_die(philo))
			*f = 1;
	}
	pthread_mutex_unlock(&philo->my_mut[*i]->fork);
	pthread_mutex_unlock(&philo->my_mut[*i2]->fork);
	philo->my_mut[*i]->flag_fork = 0;
	philo->my_mut[*i2]->flag_fork = 0;
	if (*f)
		return (print_died(philo));
	do_philo(philo, 3);
	*f = get_time_mls();
	while (get_time_mls() < (*f + philo->time_sleep))
	{
		if (philo_die(philo))
			return (print_died(philo));
	}
	return (0);
}

size_t	time_philo(t_philo *philo, size_t i, size_t i2, size_t f)
{
	if (cheack_eat_philo(philo, &i, &i2))
		return (1);
	if (cheack_eat_philo_2(philo, &i, &i2, &f))
		return (1);
	if (philo_die(philo))
		return (print_died(philo));
	do_philo(philo, 4);
	if (philo->flag_count_each_philo)
	{
		--philo->count_each_philo;
		if (!philo->count_each_philo)
			return (2);
	}
	return (0);
}

void	*my_thread(void *ph)
{
	t_philo	*philo;
	size_t	i;

	i = 0;
	philo = (t_philo *)ph;
	philo->time_philo = get_time_mls();
	while (!i)
	{
		i = time_philo(philo, 0, 0, 0);
	}
	return (0);
}

int	start(t_philo **philo, size_t count, size_t i)
{
	philo[0]->my_mut[0]->flag_dead = 0;
	while (i < count)
	{
		pthread_create(&(philo[i]->my_thread), NULL, my_thread, philo[i]);
		++i;
	}
	i = 0;
	while (i < count)
	{
		pthread_join(philo[i]->my_thread, NULL);
		++i;
	}
	return (0);
}
