/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:01:53 by waalexan          #+#    #+#             */
/*   Updated: 2024/09/04 15:01:54 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_init_philo(t_philo *philo, pthread_mutex_t *forks,
		pthread_mutex_t *messager, t_program *program)
{
	int	i;

	i = 0;
	while (i < program->n_philo)
	{
		philo[i].id = i + 1;
		philo[i].eaten = 0;
		philo[i].no_eat = 0;
		philo[i].messager = messager;
		philo[i].program = program;
		philo[i].fork = forks;
		philo[i].last_snack = ft_timestamp();
		i++;
	}
}

void	ft_init_mutex(pthread_mutex_t *fork, pthread_mutex_t *messager,
		int n_philo)
{
	int	i;

	i = 0;
	while (i < n_philo)
	{
		if (pthread_mutex_init(&fork[i], NULL) != 0)
		{
			perror("Failed to initialize mutex");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	if (pthread_mutex_init(messager, NULL) != 0)
	{
		perror("Failed to initialize message mutex");
		exit(EXIT_FAILURE);
	}
}

void	ft_pthread_create(pthread_t *thread, t_philo *philo, int n_philo)
{
	int	i;

	i = 0;
	while (i < n_philo)
	{
		if (pthread_create(&thread[i], NULL, &ft_routine, &philo[i]) != 0)
		{
			perror("Failed to create thread");
			exit(EXIT_FAILURE);
		}
		usleep(100);
		i++;
	}
}

void	ft_join_thread(pthread_t *thread, int n_philo)
{
	int	i;

	i = 0;
	while (i < n_philo)
	{
		if (pthread_join(thread[i], NULL) != 0)
		{
			perror("Failed to join thread");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	ft_mutex_destroy(pthread_mutex_t *fork, pthread_mutex_t *messager,
		int n_philo)
{
	int	i;

	i = 0;
	while (i < n_philo)
	{
		pthread_mutex_destroy(&fork[i]);
		i++;
	}
	pthread_mutex_destroy(messager);
}
