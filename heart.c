/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heart.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 08:55:05 by waalexan          #+#    #+#             */
/*   Updated: 2024/08/30 08:39:27 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		pthread_mutex_lock(philo->fork_left);
		ft_messager(philo, "took the left fork", "🍴");
		pthread_mutex_lock(philo->fork_right);
		ft_messager(philo, "took the right fork", "🍴");
		philo->eaten++;
		ft_messager(philo, "is eating", "🍜");
		usleep(philo->program->t_eat * 1000);
		philo->last_snack = ft_timestamp();
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		ft_messager(philo, "is sleeping", "💤");
		usleep(philo->program->t_sleep * 1000);
		ft_messager(philo, "is thinking", "🧠");
	}
	return (NULL);
}

static void	ft_all_done(t_program *program, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < program->n_philo)
	{
		if (philos[i].eaten < program->n_snack)
			return ;
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
		exit(0);
	}
}

int	ft_monitoring(t_philo *philos)
{
	int			i;
	t_program	*program;

	program = philos[0].program;
	while (1)
	{
		i = 0;
		while (i < program->n_philo)
		{
			if (ft_timestamp()
				- philos[i].last_snack > (unsigned long)program->t_dead)
			{
				ft_messager(&philos[i], "is dead", "💀");
				return (1);
			}
			i++;
		}
		ft_all_done(program, philos);
		usleep(1000);
	}
	return (0);
}
