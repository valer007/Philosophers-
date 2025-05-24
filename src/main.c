/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 23:22:23 by vmakarya          #+#    #+#             */
/*   Updated: 2025/05/24 23:59:03 by vmakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philo_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	pthread_mutex_lock(&philo->data->finish_mutex);
	if (philo->data->max_meals != -1
		&& philo->meals_eaten >= philo->data->max_meals)
	{
		philo->data->finish = 1;
		pthread_mutex_unlock(&philo->data->finish_mutex);
		pthread_mutex_unlock(&philo->meal_mutex);
		return (1);
	}
	if (timestamp() - philo->last_meal >= philo->data->time_to_die)
	{
		philo->data->finish = 1;
		printf("%ld %d died\n", timestamp() - philo->data->start_time,
			philo->id);
		pthread_mutex_unlock(&philo->data->finish_mutex);
		pthread_mutex_unlock(&philo->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->finish_mutex);
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
}

static int	monitoring(t_data *data)
{
	int		i;

	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (check_philo_status(&data->philos[i]))
				return (1);
			i++;
		}
		ft_usleep(10);
	}
	return (0);
}

static void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->stop_mutex);
	print_action(philo, "hase taken a fork");
	ft_usleep(philo->data->time_to_die);
	print_action(philo, "died");
	pthread_mutex_unlock(&philo->stop_mutex);
}

static int	start_threads_and_monitor(t_data *data)
{
	int	i;

	if (data->nb_philo == 1)
	{
		one_philo(&data->philos[0]);
		destroy_philo(data);
		return (0);
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_create(&data->philos[i].philo,
			NULL, routine, (void *)&(data->philos[i]));
		i++;
	}
	monitoring(data);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].philo, NULL);
		i++;
	}
	destroy_philo(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		printf("invalid arguments count\n");
		return (0);
	}
	if (!check_args(argv))
		return (0);
	if (!init_data(&data, argv))
	{
		printf("initialization error\n");
		return (0);
	}
	init_philo(&data, argv);
	start_threads_and_monitor(&data);
	return (0);
}
