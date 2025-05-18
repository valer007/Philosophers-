#include "philo.h"

// void eat(t_philo *philo)
// {
// 	pthread_mutex_lock(philo->left_fork);
// 	print_action(philo, "has taken a fork");
// 	pthread_mutex_lock(philo->right_fork);
// 	print_action(philo, "has taken a fork");
// 	print_action(philo, "is eating");
// 	philo->last_meal  = my_gettime();
// 	ft_usleep(philo->data->time_to_eat);
// 	philo->meals_eaten++;
// 	pthread_mutex_unlock(philo->left_fork);
// 	pthread_mutex_unlock(philo->right_fork);
// }

void one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a left fork");
	ft_usleep(philo->data->time_to_die);
	print_action(philo, "died");
	pthread_mutex_unlock(philo->left_fork);
}

void eat(t_philo *philo)
{
	if (philo->id == philo->data->philo_count)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a left fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a right fork");
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else {
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a right fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a left fork");
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!philo->data->finished)
	{
		if (philo->data->max_meals != -1 &&
			philo->meals_eaten >= philo->data->max_meals)
			break ;
		eat(philo);
		philo->meals_eaten++;
		print_action(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		print_action(philo, "is thinking");
	}
	return (NULL);
}
