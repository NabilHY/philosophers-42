/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:23:25 by nhayoun           #+#    #+#             */
/*   Updated: 2024/06/09 20:13:36 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	print_status(char state, int id, t_philo *ph)
{
	sem_wait(ph->env->print);
	if (ph->env->end_sim == true)
	{
		sem_post(ph->env->print);
		return ;
	}
	if (state == 'T')
		printf("%lu %u is thinking\n", timestamp(ph->start_sim), id);
	else if (state == 'E')
		printf("%lu %u is eating\n", timestamp(ph->start_sim), id);
	else if (state == 'S')
		printf("%lu %u is sleeping\n", timestamp(ph->start_sim), id);
	else if (state == 'F')
		printf("%lu %u has taken a fork\n", timestamp(ph->start_sim), id);
	else if (state == 'D')
	{
		printf("%lu %u died\n", timestamp(ph->start_sim), id);
		ph->env->end_sim = true;
	}
	sem_post(ph->env->print);
}

void	kill_all(t_philo *philos, int npss)
{
	int	i;

	i = 0;
	while (i < npss)
	{
		printf("ps_id : %d\n", philos[i].psid);
		kill(philos[i].psid, SIGKILL);
		i++;
	}
}

void	*philo_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		print_status('S', philo->id, philo);
		suspend(philo->env->tsleep);
	}
	while (philo->times_eaten != 0 && !philo->env->end_sim)
	{
		print_status('T', philo->id, philo);
		sem_wait(philo->env->forks);
		print_status('F', philo->id, philo);
		if (philo->env->nu_philos == 1)
			return (NULL);
		sem_wait(philo->env->forks);
		print_status('F', philo->id, philo);
		print_status('E', philo->id, philo);
		sem_wait(philo->env->update_elapsed);
		philo->last_eaten = current_time();
		philo->times_eaten--;
		sem_post(philo->env->update_elapsed);
		sem_post(philo->env->forks);
		sem_post(philo->env->forks);
		suspend(philo->env->teat);
		print_status('S', philo->id, philo);
		suspend(philo->env->tsleep);
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if ((current_time() - philo->last_eaten) > philo->env->tdie)
		{
			sem_wait(philo->env->print);
			printf("%lu %u died\n", timestamp(philo->start_sim), philo->id);
			exit(1);
		}
	}
	return (NULL);
}

void	*simulation(t_env *env)
{
	int i;
	int status;
	pid_t *pid;
	t_philo *philo;

	i = 0;
	while (i < env->nu_philos)
	{
		philo = &env->philos[i];
		philo->start_sim = current_time();

		printf("pid : %d\n", *pid);
		*pid = fork();
		if (!*pid)
		{
			if (pthread_create(&philo->thid, NULL, monitor, (void *)philo))
			{
				printf("Error creating thread!\n");
				exit(0);
			}
			philo_routine(&env->philos[i]);
			pthread_join(philo->thid, NULL);
		}
		i++;
	}
	i = 0;
	while (waitpid(-1, &status, 0))
	{
		if (status != 0)
		{
			kill_all(env->philos, env->nu_philos);
			break ;
		}
	}
	return (NULL);
}