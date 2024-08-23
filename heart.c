/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heart.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:56:42 by waalexan          #+#    #+#             */
/*   Updated: 2024/08/23 14:14:32 by waalexan         ###   ########.fr       */
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

void	*ft_monitoring(void *ptr)
{
	int	i;
	int	all_done;
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
			if (current_time - philos[i].last_snack
				> (unsigned long)program->t_dead)
			{
				pthread_mutex_lock(philos[i].messager);
				printf("💀 %ldms Philo %d morreu\n",
					display_time(&philos[i]), philos[i].id);
				pthread_mutex_unlock(philos[i].messager);
				exit(1);
			}
			i++;
		}
		all_done = 0;
		i = 0;
		while (i < program->n_philo)
		{
			if (philos[i].eaten < program->n_snack)
			{
				all_done = 1;
				break ;
			}
			i++;
		}
		if (!all_done && program->n_snack > 0)
		{
			printf("🎉 all done eaten \nREPORT\n");
			i = -1;
			while (++i < program->n_philo)
				printf("philo number %d eaten %d snack\n",
					philos[i].id, philos[i].eaten);
			exit(0);
		}
		usleep(1000);
	}
	return (NULL);
}
