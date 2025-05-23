/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:23:58 by vmakarya          #+#    #+#             */
/*   Updated: 2025/05/23 22:33:38 by vmakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int check_count(t_philo *philo)
// {
// 	if (philo->data->max_meals != -1 && philo->meals_eaten >= philo->data->max_meals)
// 		return (1);
// 	return (0);
// }

int check_args(char **argv)
{
	int i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("invalide argumnents\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

long timestamp(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long long ms)
{
	long	start = timestamp();
	while ((timestamp() - start) < ms)
		usleep(50);
}

int	ft_atoi(const char *str)
{
	int i = 0;
	int res = 0;
	while (str[i] == '\n' || str[i] == ' ' || str[i] == '\t'
		|| str[i] == '\f' || str[i] == '\v' || str[i] == '\r')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	return (res);
}

void print_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->data->finish_mutex);
	if (*(philo->finished))
	{
		pthread_mutex_unlock(&philo->data->finish_mutex);
		return;
	}
	pthread_mutex_unlock(&philo->data->finish_mutex);
	pthread_mutex_lock(&philo->write_mutex);
	printf("%ld %d %s\n", timestamp() - philo->data->start_time, philo->id, action);
	pthread_mutex_unlock(&philo->write_mutex);
}

void destroy_philo(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&(data->finish_mutex));
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&(data->philos[i].meal_mutex));
		pthread_mutex_destroy(&(data->philos[i].stop_mutex));
		pthread_mutex_destroy(&(data->forks[i]));
		i++;
	}
	free(data->philos);
	free(data->forks);
}