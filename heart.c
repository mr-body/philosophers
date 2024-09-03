/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heart.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 08:55:05 by waalexan          #+#    #+#             */
/*   Updated: 2024/09/03 09:48:25 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_take_forks(t_philo *philo)
{
	if (philo->fork_left < philo->fork_right)
	{
		pthread_mutex_lock(philo->fork_left);
		ft_messager(philo, "took the left fork", "🍴");
		pthread_mutex_lock(philo->fork_right);
		ft_messager(philo, "took the right fork", "🍴");
	}
	else
	{
		pthread_mutex_lock(philo->fork_right);
		ft_messager(philo, "took the right fork", "🍴");
		pthread_mutex_lock(philo->fork_left);
		ft_messager(philo, "took the left fork", "🍴");
	}
}

static void	case_one(t_philo *philo)
{
	printf("🍴 %ldms Philo %d took a fork\n", display_time(philo), philo->id);
	usleep(philo->program->t_dead * 1000);
	printf("💀 %ldms Philo %d is dead\n", display_time(philo), philo->id);
	set_is_dead(philo->program, 1);
}

void	*ft_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->program->n_philo == 1)
		case_one(philo);
	else
	{
		while (!get_is_dead(philo->program))
		{
			ft_take_forks(philo);
			set_eaten(philo, get_eaten(philo) + 1);
			ft_messager(philo, "is eating", "🍜");
			usleep(philo->program->t_eat * 1000);
			set_last_snack(philo, ft_timestamp());
			pthread_mutex_unlock(philo->fork_right);
			pthread_mutex_unlock(philo->fork_left);
			ft_messager(philo, "is sleeping", "💤");
			usleep(philo->program->t_sleep * 1000);
			ft_messager(philo, "is thinking", "🧠");
		}
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
	}
	if (program->n_snack > 0)
	{
		printf("🎉 Everyone ate food \nSummary\n");
		i = 0;
		while (i < program->n_philo)
		{
			printf("Philo number %d eaten %d snack\n", philos[i].id,
				philos[i].eaten);
			i++;
		}
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
			if (ft_timestamp()
				- get_last_snack(&philos[i]) > (unsigned long)program->t_dead)
			{
				ft_messager(&philos[i], "is dead", "💀");
				set_is_dead(program, 1);
				break ;
			}
		}
		if (ft_all_done(program, philos))
		{
			set_is_dead(program, 1);
			break ;
		}
		usleep(1000);
	}
	return (0);
}
