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

typedef struct s_my_mutexs
{
	pthread_mutex_t	fork;
	int				flag_fork;
	int				flag_dead;
}					t_my_mutexs;

typedef struct s_philo
{
	pthread_t	my_thread;
	t_my_mutexs	**my_mut;
	size_t		count;
	size_t		ip_philo;
	size_t		time_philo;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_sleep;
	size_t		count_each_philo;
	size_t		flag_count_each_philo;
}				t_philo;

int 	cheack_inic_argv(t_philo ***philo, int argc, char **argv);

long	ft_atoi(const char *nptr);
int		ft_isdigit(int a );
int		ft_strlen(char *a );
int		chack_number(char *mas);
int		ft_strlen_zero(char *a , int i, int j, int f);

int		initalizatia_mut(t_my_mutexs ***my_mut, size_t size, size_t i, size_t f);

int		start(t_philo **philo, size_t count, size_t i);
size_t	get_time_mls();
int		philo_die(t_philo *philo);
int		print_died(t_philo *philo);
void	do_philo(t_philo *philo, size_t i);

#endif