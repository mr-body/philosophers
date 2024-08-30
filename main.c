/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 08:55:39 by waalexan          #+#    #+#             */
/*   Updated: 2024/08/30 08:45:14 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_valid_arg(int ac, char **av, t_program *program)
{
	if (ac > 6 || ac < 5)
	{
		printf("Usage: %s philo dead eat sleep [snack]\n", av[0]);
		exit(EXIT_FAILURE);
	}
	program->n_philo = atoi(av[1]);
	program->t_dead = atoi(av[2]);
	program->t_eat = atoi(av[3]);
	program->t_sleep = atoi(av[4]);
	program->time = ft_timestamp();
	if (ac == 6)
	{
		program->n_snack = atoi(av[5]);
		if (program->n_snack <= 0)
		{
			printf("The number of snacks must be positive or greater than 0\n");
			exit(EXIT_FAILURE);
		}
	}
	else
		program->n_snack = 0;
}

int	main(int ac, char **av)
{
	t_program		program;
	t_philo			*philo;
	pthread_t		*thread;
	pthread_mutex_t	*messager;
	pthread_mutex_t	*fork;

	ft_valid_arg(ac, av, &program);
	philo = (t_philo *)malloc(sizeof(t_philo) * program.n_philo);
	thread = (pthread_t *)malloc(sizeof(pthread_t) * program.n_philo);
	fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * program.n_philo);
	messager = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* program.n_philo);
	ft_init_philo(philo, fork, messager, &program);
	ft_init_mutex(messager, fork, program.n_philo);
	ft_pthread_create(thread, philo, program.n_philo);
	if (ft_monitoring(philo))
	{
		free(philo);
		free(thread);
		free(fork);
		free(messager);
		return (0);
	}
	ft_join_thread(thread, program.n_philo);
	ft_mutex_destroy(fork, messager, program.n_philo);
	return (0);
}
