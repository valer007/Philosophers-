/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:37:35 by vmakarya          #+#    #+#             */
/*   Updated: 2025/05/17 17:20:55 by vmakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #ifndef PHILO_H
// # define PHILO_H

// # include <stdio.h>
// # include <unistd.h>
// # include <pthread.h>
// # include <stdlib.h>
// # include <sys/time.h>

// typedef struct s_data t_data;

// typedef struct s_philo
// {
// 	int				id;
// 	long long		last_meal;
// 	int				meals_eaten;
// 	pthread_t       thread;
// 	pthread_mutex_t *left_fork;
// 	pthread_mutex_t *right_fork;
// 	t_data 			*data;
// } t_philo;

// typedef struct s_data
// {
// 	pthread_mutex_t *forks;
// 	t_philo			*philos;
// 	pthread_mutex_t	write_mutex;
// 	int				finished;
// 	int				max_meals;
// 	int				time_to_sleep;
// 	int				time_to_eat;
// 	int				time_to_die;
// 	int				philo_count;
// 	int				start;
// } t_data;

// void				*routine(void *arg);
// void				my_usleep(long long ms);
// void				init_philos(t_data *tp);
// int 				initializer(t_data *obj, char **argv, int argc);
// int 				check_args(char **argv);
// int 				ft_atoi (char *num);
// long long 			my_gettime();
// void				print_action(t_philo *philo, char *msg);

// #endif

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
	long long       last_meal;
	pthread_t       thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	t_data          *data;
}	t_philo;

typedef struct s_data
{
	int             philo_count;
	int             time_to_die;
	int             time_to_eat;
	int             time_to_sleep;
	int             max_meals;
	int             finished;
	long long       start;
	pthread_mutex_t *forks;
	pthread_mutex_t write_mutex;
	t_philo         *philos;
}	t_data;

void		one_philo(t_philo *philo);
int			initializer(t_data *data, char **argv, int argc);
void		init_philos(t_data *tp);
long long	my_gettime(void);
void		ft_usleep(long long ms);
int			ft_atoi(char *str);
void		print_action(t_philo *philo, char *msg);
void		*routine(void *arg);

#endif
