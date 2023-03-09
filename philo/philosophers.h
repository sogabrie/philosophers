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

typedef struct s_my_mutexs
{
	pthread_mutex_t	*fork;
	int				flag_fork;
}					t_my_mutexs;

typedef struct s_philo
{
	t_my_mutexs	*my_mut;
	size_t		ip_philo;
	int			time_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			count_each_philo;

}				t_philo;

int cheack_inic_argv(t_my_mutexs *philo, int argc,char **argv);

#endif