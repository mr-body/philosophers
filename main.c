/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 08:55:39 by waalexan          #+#    #+#             */
/*   Updated: 2024/09/03 09:10:25 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_exit_arg(int code)
{
	if (code == 501)
		printf("use: ./philosophers philo dead eat sleep [snack]\n");
	else if (code == 502)
		printf("The Philo number cannot exceed 200\n");
	else if (code == 503)
		printf("The number of snacks must be positive or greater than 0\n");
	exit(1);
}

static void	ft_valid_arg(int ac, char **av, t_program *program)
{
	if (ac > 6 || ac < 5)
		ft_exit_arg(501);
	if ((ft_atoi(av[1]) > MAX_PHILO))
		ft_exit_arg(502);
	program->n_philo = ft_atoi(av[1]);
	program->t_dead = ft_atoi(av[2]);
	program->t_eat = ft_atoi(av[3]);
	program->t_sleep = ft_atoi(av[4]);
	program->time = ft_timestamp();
	program->is_dead = 0;
	if (ac == 6)
	{
		program->n_snack = ft_atoi(av[5]);
		if (program->n_snack <= 0)
			ft_exit_arg(503);
	}
	else
		program->n_snack = 0;
}

int	main(int ac, char **av)
{
	t_program		program;
	t_philo			*philo;
	pthread_t		*thread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	messager;

	ft_valid_arg(ac, av, &program);
	init_program_mutex(&program);
	philo = (t_philo *)malloc(sizeof(t_philo) * program.n_philo);
	thread = (pthread_t *)malloc(sizeof(pthread_t) * program.n_philo);
	fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * program.n_philo);
	ft_init_philo(philo, fork, &messager, &program);
	ft_init_mutex(fork, &messager, program.n_philo);
	ft_pthread_create(thread, philo, program.n_philo);
	ft_monitoring(philo);
	ft_join_thread(thread, program.n_philo);
	ft_mutex_destroy(fork, &messager, program.n_philo);
	destroy_program_mutex(&program);
	free(philo);
	free(thread);
	free(fork);
	return (0);
}
