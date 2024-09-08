/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:11:57 by waalexan          #+#    #+#             */
/*   Updated: 2024/09/03 09:45:32 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_program_mutex(t_program *program)
{
	pthread_mutex_destroy(&program->program_mutex);
}

void	set_is_dead(t_program *program, int value)
{
	pthread_mutex_lock(&program->program_mutex);
	program->is_dead = value;
	pthread_mutex_unlock(&program->program_mutex);
}

void	set_all_eaten(t_program *program, int value)
{
	pthread_mutex_lock(&program->program_mutex);
	program->all_eaten = value;
	pthread_mutex_unlock(&program->program_mutex);
}

void	set_last_snack(t_philo *philo, unsigned long int value)
{
	pthread_mutex_lock(philo->messager);
	philo->last_snack = value;
	pthread_mutex_unlock(philo->messager);
}

void	set_no_eat(t_philo *philo, int value)
{
	pthread_mutex_lock(&philo->program->program_mutex);
	philo->no_eat = value;
	pthread_mutex_unlock(&philo->program->program_mutex);
}
