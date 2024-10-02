/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 08:54:50 by waalexan          #+#    #+#             */
/*   Updated: 2024/09/03 09:14:59 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static int	ft_varg(char *s)
{
	if (*s == '+')
		s++;
	while (*s)
	{
		if (!(*s >= '0' && *s <= '9'))
			return (1);
		s++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	if (ft_varg(str))
	{
		printf("error: invalid argument\n");
		return (-1);
	}
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}

unsigned long	ft_timestamp(void)
{
	struct timeval	timespamp;
	unsigned long	l;
	unsigned long	s;
	unsigned long	u;

	if (gettimeofday(&timespamp, NULL) != 0)
	{
		printf("Failed to get time");
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

void	ft_messager(t_philo *philo, char *info, char *color)
{
	pthread_mutex_lock(philo->messager);
	if (!get_is_dead(philo->program) && !get_all_eaten(philo->program))
	{
		if (get_no_eat(philo) == 0)
		{
			printf("%s %ldms %d %s\033[0m\n", color, display_time(philo),
				philo->id, info);
		}
	}
	pthread_mutex_unlock(philo->messager);
}
