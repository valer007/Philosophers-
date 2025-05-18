#include "philo.h"

long long my_gettime(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long long ms)
{
	long long	start = my_gettime();
	while ((my_gettime() - start) < ms)
		usleep(100);
}

int	ft_atoi(char *str)
{
	int i = 0;
	int res = 0;
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	return (res);
}

void	print_action(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->write_mutex);
	if (!philo->data->finished)
		printf("%lld %d %s\n", my_gettime() - philo->data->start, philo->id, msg);
	pthread_mutex_unlock(&philo->data->write_mutex);
}
