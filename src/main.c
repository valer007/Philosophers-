#include "philo.h"

void monitoring(t_data *data)
{
	int	i;

	if (!data->finished)
	{
		i = 0;
		while (i < data->philo_count)
		{
			if (my_gettime() - data->philos[i].last_meal > (long long)data->time_to_die)
			{
				data->finished = 1;
				print_action(&data->philos[i], "died");
				return ;
			}
			i++;
		}
		usleep(1000);
	}
}

int check_args(char **argv)
{
	int i;
	int j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int main(int argc, char **argv)
{
	t_data 	data;
	int 	i;

	i = 0;
	if(argc != 5 && argc != 6)
	 	return (1);
	if (!check_args(argv))
		return (printf("invalid arguments"));
	if (!initializer(&data, argv, argc))
		return (printf("Initialization failed\n"), 1);
	init_philos(&data);
	if (argv[1][0] == '1')
		return (one_philo(data.philos), 0);
	while (i < data.philo_count)
	{
		pthread_create(&data.philos[i].thread, NULL, routine, &data.philos[i]);
		i++;
	}
	monitoring(&data);
	i = 0;
	while (i < data.philo_count)
		pthread_join(data.philos[i++].thread, NULL);
	return (0);
}
