/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heart.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:01:43 by waalexan          #+#    #+#             */
/*   Updated: 2024/09/04 15:01:44 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	case_one(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork[philo->id - 1]);
	ft_messager(philo, "has taken a fork", "\033[0;36m");
	usleep(philo->program->t_dead * 1000);
	pthread_mutex_unlock(&philo->fork[philo->id - 1]);
}

static void	ft_take_forks(t_philo *philo)
{
	if (philo->id - 1 < philo->id % philo->program->n_philo)
	{
		pthread_mutex_lock(&philo->fork[philo->id - 1]);
		ft_messager(philo, "has taken a fork", "\033[0;36m");
		pthread_mutex_lock(&philo->fork[philo->id % philo->program->n_philo]);
		ft_messager(philo, "has taken a fork", "\033[0;36m");
	}
	else
	{
		pthread_mutex_lock(&philo->fork[philo->id % philo->program->n_philo]);
		ft_messager(philo, "has taken a fork", "\033[0;36m");
		pthread_mutex_lock(&philo->fork[philo->id - 1]);
		ft_messager(philo, "has taken a fork", "\033[0;36m");
	}
}

void	*ft_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->program->n_philo == 1)
		return (case_one(philo), NULL);
	while (!get_is_dead(philo->program))
	{
		if (get_no_eat(philo) == 0)
			ft_take_forks(philo);
		if (philo->no_eat == 0)
			ft_messager(philo, "is eating", "\033[0;32m");
		set_last_snack(philo, ft_timestamp());
		set_eaten(philo, get_eaten(philo) + 1);
		if ((philo->program->n_snack > 0)
			&& philo->eaten >= philo->program->n_snack)
			set_no_eat(philo, 1);
		usleep(philo->program->t_eat * 1000);
		pthread_mutex_unlock(&philo->fork[philo->id - 1]);
		pthread_mutex_unlock(&philo->fork[philo->id % philo->program->n_philo]);
		ft_messager(philo, "is sleeping", "\033[0;34m");
		usleep(philo->program->t_sleep * 1000);
		ft_messager(philo, "is thinking", "\033[0;33m");
	}
	return (NULL);
}

static int	ft_all_done(t_program *program, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < program->n_philo)
	{
		if (get_eaten(&philos[i]) < program->n_snack)
			return (0);
		i++;
		usleep(1000);
	}
	if (program->n_snack > 0)
	{
		set_all_eaten(program, 1);
		return (1);
	}
	return (0);
}

int	ft_monitoring(t_philo *philos)
{
	int			i;
	t_program	*program;

	program = philos[0].program;
	while (!get_is_dead(program))
	{
		i = -1;
		while (++i < program->n_philo)
		{
			if (ft_timestamp() - get_last_snack(&philos[i])
				> (unsigned long)(program->t_dead) + 4)
			{
				ft_messager(&philos[i], "is dead", "\033[0;31m");
				set_is_dead(program, 1);
				return (0);
			}
		}
		if (ft_all_done(program, philos))
		{
			return (set_is_dead(program, 1), 0);
		}
		usleep(500);
	}
	return (0);
}
