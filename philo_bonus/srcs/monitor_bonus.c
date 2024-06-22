/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:13:11 by nhayoun           #+#    #+#             */
/*   Updated: 2024/06/22 20:05:55 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	kill_all(t_philo *philos, int philos_nu)
{
	int	i;

	i = 0;
	while (i < philos_nu)
	{
		kill(philos[i].psid, SIGKILL);
		i++;
	}
}

void	*food_monitor(void *arg)
{
	t_env	*env;
	int		i;

	i = 0;
	env = (t_env *)arg;
	sem_wait(env->full);
	kill_all(env->philos, env->nu_philos);
	exit(0);
	return (NULL);
}

void	*death_monitor(void *arg)
{
	t_env	*env;
	int		i;

	i = 0;
	env = (t_env *)arg;
	sem_wait(env->death);
	kill_all(env->philos, env->nu_philos);
	exit(0);
	return (NULL);
}

void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->env->end_sim)
	{
		sem_wait(philo->env->update_elapsed);
		if ((current_time() - philo->last_eaten) >= philo->env->tdie)
		{
			print_status('D', philo->id, philo);
		}
		sem_post(philo->env->update_elapsed);
	}
	return (NULL);
}

void	destroy_sem(t_env *env)
{
	sem_close(env->update_elapsed);
	sem_unlink(ELAPSED);
	sem_close(env->forks);
	sem_unlink(FORKS);
	sem_close(env->print);
	sem_unlink(PRINT);
	sem_close(env->full);
	sem_unlink(FULL);
	sem_close(env->death);
	sem_unlink(DEATH);
}
