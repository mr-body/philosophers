/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:46:12 by waalexan          #+#    #+#             */
/*   Updated: 2024/08/23 11:00:16 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_init_philo(t_philo *philo, pthread_mutex_t *fork,
		pthread_mutex_t *messager, t_program *program)
{
	int	i;

	i = -1;
	while (++i < program->n_philo)
	{
		philo[i].id = i + 1;
		philo[i].eaten = 0;
		philo[i].fork_left = &fork[i];
		philo[i].messager = &messager[i];
		philo[i].fork_rigth = &fork[(i + 1) % program->n_philo];
		philo[i].program = program;
		philo[i].last_snack = ft_timestamp();
	}
}

void	ft_init_mutex(pthread_mutex_t *messager, pthread_mutex_t *fork,
		int n_philo)
{
	int	i;

	i = -1;
	while (++i < n_philo)
	{
		pthread_mutex_init(&fork[i], NULL);
		pthread_mutex_init(&messager[i], NULL);
	}
}

void	ft_pthread_create(pthread_t *thread, t_philo *philo, int n_philo)
{
	int	i;

	i = -1;
	while (++i < n_philo)
	{
		if (pthread_create(&thread[i], NULL, &ft_routine, &philo[i]) != 0)
		{
			perror("Failed to create thread");
			exit(1);
		}
		usleep(100);
	}
}

void	ft_join_thread(pthread_t *thread, int n_philo)
{
	int	i;

	i = -1;
	while (++i < n_philo)
	{
		if (pthread_join(thread[i], NULL) != 0)
		{
			perror("Failed to join thread");
			exit(1);
		}
	}
}

void	ft_mutex_destroy(pthread_mutex_t *fork, pthread_mutex_t *messager,
		int n_philo)
{
	int	i;

	i = -1;
	while (++i < n_philo)
	{
		pthread_mutex_destroy(&fork[i]);
		pthread_mutex_destroy(&messager[i]);
	}
}
