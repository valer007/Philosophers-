#include "philo.h"

int initializer(t_data *data, char **argv, int argc)
{
	int i;

	data->philo_count = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->max_meals = (argc == 6) ? ft_atoi(argv[5]) : -1;
	data->finished = 0;
	data->start = my_gettime();
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->forks || !data->philos)
		return (0);
	pthread_mutex_init(&data->write_mutex, NULL);
	i = 0;
	while (i < data->philo_count)
		pthread_mutex_init(&data->forks[i++], NULL);
	return (1);
}

void init_philos(t_data *tp)
{
	int i; 

	i = 0;
	while (i < tp->philo_count)
	{
		tp->philos[i].id = i + 1;
		tp->philos[i].left_fork = &tp->forks[i];
		tp->philos[i].right_fork  = &tp->forks[(i + 1) % tp->philo_count];
		tp->philos[i].last_meal = tp->start;
		tp->philos[i].data = tp;
		tp->philos[i].meals_eaten = 0;
		i++;
	}
}
