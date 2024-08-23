/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heart.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:56:42 by waalexan          #+#    #+#             */
/*   Updated: 2024/08/23 11:25:34 by waalexan         ###   ########.fr       */
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
		ft_messager(philo, "pegou o garfo da esquerda", "🍴");
		pthread_mutex_lock(philo->fork_rigth);
		ft_messager(philo, "pegou o garfo da direita", "🍴");
		philo->eaten++;
		ft_messager(philo, "Está comendo", "🍜");
		usleep(philo->program->t_eat * 1000);
		philo->last_snack = ft_timestamp();
		pthread_mutex_unlock(philo->fork_rigth);
		pthread_mutex_unlock(philo->fork_left);
		ft_messager(philo, "Está Dormindo", "💤");
		usleep(philo->program->t_sleep * 1000);
		ft_messager(philo, "Está Pensando", "🧠");
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
		printf("🎉 all done eaten \nREPORT\n");
		i = -1;
		while (++i < program->n_philo)
			printf("philo number %d eaten %d snack\n", philos[i].id,
				philos[i].eaten);
		exit(0);
	}
}

void	*ft_monitoring(void *ptr)
{
	int				i;
	unsigned long	current_time;
	t_philo			*philos;
	t_program		*program;

	philos = (t_philo *)ptr;
	program = philos[0].program;
	while (1)
	{
		i = 0;
		while (i < program->n_philo)
		{
			current_time = ft_timestamp();
			if (current_time
				- philos[i].last_snack > (unsigned long)program->t_dead)
			{
				ft_messager(philos, "morreu", "💀");
				exit(1);
			}
			i++;
		}
		ft_all_done(program, philos);
		usleep(1000);
	}
	return (NULL);
}
