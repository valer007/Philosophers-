/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <vmakarya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 23:22:24 by vmakarya          #+#    #+#             */
/*   Updated: 2025/06/03 15:15:01 by vmakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_died(t_philo *philo)
{
	int	die;

	if (philo->data->max_meals != -1
		&& philo->meals_eaten >= philo->data->max_meals)
		return (1);
	pthread_mutex_lock(&philo->data->finish_mutex);
	die = *(philo->finished);
	pthread_mutex_unlock(&philo->data->finish_mutex);
	return (die);
}

static void	eat(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a left fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a right fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a right fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a left fork");
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!is_died(philo))
	{
		eat(philo);
		pthread_mutex_lock(&philo->meal_mutex);
		philo->last_meal = timestamp();
		pthread_mutex_unlock(&philo->meal_mutex);
		print_action(philo, "is eating");
		ft_usleep(philo->time_to_eat);
		philo->meals_eaten++;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_action(philo, "is sleeping");
		ft_usleep(philo->time_to_sleep);
		print_action(philo, "is thinking");
	}
	return (NULL);
}
