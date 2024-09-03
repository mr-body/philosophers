/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:17:32 by waalexan          #+#    #+#             */
/*   Updated: 2024/09/03 09:43:59 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_is_dead(t_program *program)
{
	int	value;

	pthread_mutex_lock(&program->program_mutex);
	value = program->is_dead;
	pthread_mutex_unlock(&program->program_mutex);
	return (value);
}

unsigned long	get_last_snack(t_philo *philo)
{
	unsigned long	value;

	pthread_mutex_lock(philo->messager);
	value = philo->last_snack;
	pthread_mutex_unlock(philo->messager);
	return (value);
}

int	get_eaten(t_philo *philo)
{
	int	value;

	pthread_mutex_lock(philo->messager);
	value = philo->eaten;
	pthread_mutex_unlock(philo->messager);
	return (value);
}
