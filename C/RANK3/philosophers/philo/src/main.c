/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:21:14 by llopes-d          #+#    #+#             */
/*   Updated: 2023/11/14 17:10:44 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	case_one(t_philo philo)
{
	if (philo.data->args.number_of_philo == 1)
		printf("0\t1 has taken a fork\n");
}

static int	unlock_forks(t_philo philo)
{
	if (philo.data->args.number_of_philo == 1)
	{
		pthread_mutex_unlock(&philo.data->forks_mutex[philo.next_fork]);
		return (1);
	}
	pthread_mutex_unlock(&philo.data->forks_mutex[philo.own_fork]);
	pthread_mutex_unlock(&philo.data->forks_mutex[philo.next_fork]);
	return (1);
}

static void	*routine(void *args)
{
	t_philo	philo;

	philo = *(t_philo *)args;
	case_one(philo);
	while (1)
	{
		philo_eat(&philo);
		if (is_satisfied(philo) && unlock_forks(philo))
			break ;
		philo_sleep(&philo);
		philo_think(&philo);
		philo_die(philo);
		if (someone_died(philo.data))
		{
			if (philo.status == EATING)
				unlock_forks(philo);
			break ;
		}
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	int		number_of_philo;
	int		i;

	if (argc == 6 && ft_atoi(argv[5]) == 0)
		return (0);
	if ((argc != 5 && argc != 6) || is_args_invalid(argc, argv))
		return (printf("Error\n"));
	number_of_philo = init_variables(&data, argc, argv);
	if (!number_of_philo)
		return (printf("Error\n"));
	pthread_mutex_init(&data.mutex, NULL);
	i = -1;
	while (++i < number_of_philo)
		pthread_create(&data.philo[i].philo_t, NULL, routine, &data.philo[i]);
	i = 0;
	while (i < number_of_philo)
		pthread_join(data.philo[i++].philo_t, NULL);
	i = 0;
	while (i < number_of_philo)
		pthread_mutex_destroy(&data.forks_mutex[i++]);
	pthread_mutex_destroy(&data.mutex);
	free(data.forks_mutex);
	free(data.philo);
	return (0);
}
