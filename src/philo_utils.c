/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:23:58 by vmakarya          #+#    #+#             */
/*   Updated: 2025/05/24 23:47:23 by vmakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long long ms)
{
	long	start;

	start = timestamp();
	while ((timestamp() - start) < ms)
		usleep(50);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i] == '\n' || str[i] == ' ' || str[i] == '\t'
		|| str[i] == '\f' || str[i] == '\v' || str[i] == '\r')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	return (res);
}

void	print_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->data->finish_mutex);
	if (*(philo->finished))
	{
		pthread_mutex_unlock(&philo->data->finish_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->finish_mutex);
	pthread_mutex_lock(&philo->write_mutex);
	printf("%ld %d %s\n", timestamp() - philo->data->start_time,
		philo->id, action);
	pthread_mutex_unlock(&philo->write_mutex);
}

void	destroy_philo(t_data *data)
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
