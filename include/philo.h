#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data t_data;

typedef struct s_philo
{
	int             id;
	int             meals_eaten;
	int             time_to_eat;
	int             time_to_sleep;
	long	       	last_meal;
	int				stop;
	int             *finished;
	pthread_t		philo;
	pthread_mutex_t meal_mutex;
	pthread_mutex_t stop_mutex;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	pthread_mutex_t write_mutex;
	t_data          *data;
}	t_philo;

typedef struct s_data
{
	int             nb_philo;
	int             time_to_die;
	int             max_meals;
	int				eat_count;
	long	       	start_time;
	int				finish;
	pthread_t		check_t;
	pthread_mutex_t finish_mutex;
	pthread_mutex_t *forks;
	t_philo         *philos;
}	t_data;

int			check_count(t_data *data);
void		destroy_philo(t_data *data);
int			check_args(char **argv);
long		timestamp(void);
void		ft_usleep(long long ms);
int			ft_atoi(const char *str);
void		print_action(t_philo *philo, char *msg);
void		one_philo(t_philo *philo);

int			init_data(t_data *data, char **argv);
void		init_philo(t_data *data, char **argv);

void		*routine(void *arg);

#endif
