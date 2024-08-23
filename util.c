/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:17:54 by waalexan          #+#    #+#             */
/*   Updated: 2024/08/23 11:01:26 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	ft_timestamp(void)
{
	struct timeval	timespamp;
	unsigned long	l;
	unsigned long	s;
	unsigned long	u;

	gettimeofday(&timespamp, NULL);
	s = (timespamp.tv_sec * 1000);
	u = (timespamp.tv_usec / 1000);
	l = s + u;
	return (l);
}

unsigned long	display_time(t_philo *philo)
{
	return (ft_timestamp() - philo->program->time);
}

void	ft_messager(t_philo *philo, char *info, char *icon)
{
	pthread_mutex_lock(philo->messager);
	printf("%s %ldms Philo %d %s\n", icon, display_time(philo), philo->id,
		info);
	pthread_mutex_unlock(philo->messager);
}
