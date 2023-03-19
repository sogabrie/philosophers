/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:39:17 by sogabrie          #+#    #+#             */
/*   Updated: 2023/03/19 19:09:38 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_my_mutexs
{
	sem_t	*fork;
	sem_t	*flag_dead;
	sem_t	*flag_print;
}			t_my_mutexs;

typedef struct s_philo
{
	pid_t		pid;
	t_my_mutexs	*my_mut;
	size_t		flag_free;
	size_t		count;
	size_t		ip_philo;
	size_t		start_time;
	size_t		time_philo;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_sleep;
	size_t		count_each_philo;
	size_t		flag_count_each_philo;
}				t_philo;

int		cheack_inic_argv(t_philo ***philo, int argc, char **argv, size_t *mas);

long	ft_atoi(const char *nptr);
int		ft_isdigit(int a );
int		ft_strlen(char *a );
int		chack_number(char *mas);
int		ft_strlen_zero(char *a, int i, int j, int f);

int		initalizatia_mut(t_my_mutexs *my_mut, size_t size);

void	start(t_philo **philo, size_t count, size_t i);
size_t	get_time_mls(void);
int		philo_die(t_philo *philo);
void	do_philo(t_philo *philo, size_t i);
void	*check_died(void *pt);

int		free_philo(t_philo ***phil, int size);
int		free_mut(t_my_mutexs *mut);
//void	free_exit(t_philo ***phil);
void	*cheack_free(void *pt);

#endif