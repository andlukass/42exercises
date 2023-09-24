/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:07:23 by user              #+#    #+#             */
/*   Updated: 2023/09/24 20:06:08 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_arguments_empty(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	return (0);
}

t_args	get_args(int argc, char *argv[])
{
	t_args args;

	args.number_of_philosophers = ft_atoi(argv[1]);
	args.time_to_die = ft_atoi(argv[2]);
	args.time_to_eat = ft_atoi(argv[3]);
	args.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		args.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
		args.has_last_argument++;
	}
	else
	{
		args.number_of_times_each_philosopher_must_eat = 0;
		args.has_last_argument = 0;
	}
	return (args);
}

t_fork *init_forks(int number_of_philosophers)
{
	int	index;
	t_fork	*fork;

	fork = (t_fork *)malloc(sizeof(t_fork) * number_of_philosophers);
	if (!fork)
		exit(0);
	index = 0;
	while (index < number_of_philosophers)
	{
		fork[index].is_on_table = 1;
		index++;
	}
	return (fork);
}

t_philosopher *init_philos(int argc, char *argv[])
{
	int		index;
	int		number_of_philosophers;
	t_philosopher	*philo;

	number_of_philosophers = ft_atoi(argv[1]);
	index = 0;
	philo = (t_philosopher *)malloc(sizeof(t_philosopher) * number_of_philosophers);
	if (!philo)
		exit(0);
	while (index < number_of_philosophers)
	{
		philo[index].id = index + 1;
		philo[index].last_time_eat = 0;
		philo[index].number_of_forks = 0;
		philo[index].args = get_args(argc, argv);
		index++;
	}
	return (philo);
}

void *teste(void *data)
{
	int	index;
	int	philo_id;
	t_philosopher philo;

	philo_id = ((t_data *)data)->philo_initiated;
	philo = ((t_data *)data)->philo[philo_id];
	while (1)
	{
		if (philo.number_of_forks < 1)
		{
			usleep(1000);
			if (((t_data *)data)->fork[philo_id].is_on_table)
			{	
				printf("%lld %d has taken a fork\n",
				((t_data *)data)->total_milliseconds, philo_id + 1);
				philo.number_of_forks++;
			}
		}
		if (philo.number_of_forks == 1)
		{
			usleep(1000);
			if (((t_data *)data)->fork[philo_id + 1].is_on_table)
			{	
				printf("%lld %d has taken a fork\n",
				((t_data *)data)->total_milliseconds, philo_id + 1);
				philo.number_of_forks++;
			}
		}
	}
	return (void *)0;
}

int main(int argc, char *argv[])
{
	t_data	data;
	pthread_t ms_counter_t;

	if ((argc != 5 && argc != 6) || is_arguments_empty(argc, argv))
		return (0);

	data.philo_initiated = 0;
	data.philo = init_philos(argc, argv);
	data.fork = init_forks(data.philo[0].args.number_of_philosophers);

	pthread_create(&ms_counter_t, NULL, ms_counter, &data.total_milliseconds);
	pthread_create(&data.philo[0].philo_t, NULL, teste, &data);



	pthread_join(data.philo[0].philo_t, NULL);
	pthread_join(ms_counter_t, NULL);
	free(data.fork);
	free(data.philo);
	return (0);
}
