/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:01:58 by waalexan          #+#    #+#             */
/*   Updated: 2024/09/04 15:01:59 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_exit_arg(int code)
{
	if (code == 501)
		printf("use: ./philosophers philo dead eat sleep [snack]\n");
	else if (code == 502)
		printf("The Philo number cannot exceed 200\n");
	else if (code == 503)
		printf("The number of snacks must be positive or greater than 0\n");
	return (1);
}

static int	ft_valid_arg(int ac, char **av, t_program *program)
{
	if (ac > 6 || ac < 5)
		return (ft_exit_arg(501));
	if ((ft_atoi(av[1]) == -1) || (ft_atoi(av[2]) == -1)
		|| (ft_atoi(av[3]) == -1) || (ft_atoi(av[4]) == -1))
		return (1);
	if ((ft_atoi(av[1]) > MAX_PHILO))
		return (ft_exit_arg(502));
	program->n_philo = ft_atoi(av[1]);
	program->t_dead = ft_atoi(av[2]);
	program->t_eat = ft_atoi(av[3]);
	program->t_sleep = ft_atoi(av[4]);
	program->time = ft_timestamp();
	program->is_dead = 0;
	program->all_eaten = 0;
	if (ac == 6)
	{
		program->n_snack = ft_atoi(av[5]);
		if (program->n_snack <= 0)
			return (ft_exit_arg(503));
	}
	else
		program->n_snack = 0;
	return (0);
}

void	set_eaten(t_philo *philo, int value)
{
	pthread_mutex_lock(philo->messager);
	philo->eaten = value;
	pthread_mutex_unlock(philo->messager);
}

int	main(int ac, char **av)
{
	t_program		program;
	t_philo			*philo;
	pthread_t		*thread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	messager;

	if (ft_valid_arg(ac, av, &program))
		return (0);
	pthread_mutex_init(&program.program_mutex, NULL);
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
