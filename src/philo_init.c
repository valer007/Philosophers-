/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:41:06 by vmakarya          #+#    #+#             */
/*   Updated: 2025/05/23 17:58:33 by vmakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, char **argv)
{
	int	i;

	i = 0;
	data->eat_count = 0;
	data->finish = 0;
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	if (argv[5])
		data->max_meals = ft_atoi(argv[5]);
	else
		data->max_meals = -1;
	pthread_mutex_init(&data->finish_mutex, NULL);
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	data->start_time = timestamp();
	if (!data->philos || !data->forks)
		return (free(data->forks), free(data->philos), printf("malloc fail\n"), 0);
	while (i < data->nb_philo)
		pthread_mutex_init(&data->forks[i++], NULL);
	return (1);
}

void	init_philo(t_data *data, char **argv)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].finished = &data->finish;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].time_to_eat = ft_atoi(argv[3]);
		data->philos[i].time_to_sleep = ft_atoi(argv[4]);
		data->philos[i].meals_eaten = 0;
		data->philos[i].stop = 0;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		pthread_mutex_init(&data->philos[i].write_mutex, NULL);
		pthread_mutex_init(&data->philos[i].stop_mutex, NULL);
		pthread_mutex_init(&data->philos[i].meal_mutex, NULL);
		data->philos[i].data = data;
		i++;
	}
}
