/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 23:22:23 by vmakarya          #+#    #+#             */
/*   Updated: 2025/05/24 15:20:11 by vmakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int monitoring(t_data *data)
{
	int i;
	
	while(1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			t_philo *philo = &data->philos[i];
			pthread_mutex_lock(&philo->meal_mutex);
			pthread_mutex_lock(&data->finish_mutex);
		if (timestamp() - philo->last_meal >= data->time_to_die)
		{
			data->finish = 1;
			if (philo->meals_eaten < philo->data->max_meals)
				printf("%ld %d %s\n", timestamp() - philo->data->start_time, philo->id, "died");
			pthread_mutex_unlock(&data->finish_mutex);
			pthread_mutex_unlock(&philo->meal_mutex);
			return (1);
		}
			pthread_mutex_unlock(&data->finish_mutex);
			pthread_mutex_unlock(&philo->meal_mutex);
			i++;
		}
		ft_usleep(10);
	}
	return (0);
}

void one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->stop_mutex);
	print_action(philo, "hase taken a fork");
	ft_usleep(philo->data->time_to_die);
	print_action(philo, "died");
	pthread_mutex_unlock(&philo->stop_mutex);
}

int main(int argc, char **argv)
{
	t_data	data;
	int		i;

	i = 0;
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
	if (data.nb_philo == 1)
		return (one_philo(&data.philos[0]), destroy_philo(&data), 0);
	while (i < data.nb_philo)
	{
		pthread_create(&data.philos[i].philo, NULL, routine, (void *)&(data.philos[i]));
		i++;
	}
	monitoring(&data);
	i = 0;
	while (i < data.nb_philo)
	{
		pthread_join(data.philos[i].philo, NULL);
		i++;
	}
	destroy_philo(&data);
}

