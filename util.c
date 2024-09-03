/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 08:54:50 by waalexan          #+#    #+#             */
/*   Updated: 2024/08/29 08:54:51 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	ft_timestamp(void)
{
	struct timeval	timespamp;
	unsigned long	l;
	unsigned long	s;
	unsigned long	u;

	if (gettimeofday(&timespamp, NULL) != 0)
	{
		perror("Failed to get time");
		exit(EXIT_FAILURE);
	}
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
	if(!get_is_dead(philo->program))
	{
		printf("%s %ldms Philo %d %s\n", icon, display_time(philo), philo->id,
			info);
	}
	pthread_mutex_unlock(philo->messager);
}

