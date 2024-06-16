/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:23:25 by nhayoun           #+#    #+#             */
/*   Updated: 2024/06/16 06:18:37 by nhayoun          ###   ########.fr       */
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

void	print_status(char state, int id, t_philo *ph)
{
	sem_wait(ph->env->print);
	if (!ph->env->end_sim)
	{
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
			return ;
		}
	}
	sem_post(ph->env->print);
}

void	*monitor(void *arg)
{
	t_philo			*philo;
	unsigned long	elapsed;

	philo = (t_philo *)arg;
	while (!philo->env->end_sim)
	{
		elapsed = current_time() - philo->last_eaten;
		if (elapsed > philo->env->tdie)
		{
			print_status('D', philo->id, philo);
			exit(1);
		}
	}
	return (NULL);
}

void	*philo_routine(t_philo *philo)
{
	philo->last_eaten = current_time();
	if (pthread_create(&philo->thid, NULL, monitor, (void *)philo))
	{
		printf("Error creating thread!\n");
		exit(1);
	}
	while (philo->times_eaten != 0 && !philo->env->end_sim)
	{
		print_status('T', philo->id, philo);
		sem_wait(philo->env->forks);
		print_status('F', philo->id, philo);
		sem_wait(philo->env->forks);
		print_status('F', philo->id, philo);
		philo->last_eaten = current_time();
		philo->times_eaten--;
		print_status('E', philo->id, philo);
		suspend(philo->env->teat);
		sem_post(philo->env->forks);
		sem_post(philo->env->forks);
		print_status('S', philo->id, philo);
		suspend(philo->env->tsleep);
	}
	pthread_join(philo->thid, NULL);
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
	sem_close(env->seated);
	sem_unlink(SEATED);
	sem_close(env->sim_sem);
	sem_unlink(END_SIM);
}

void	*simulation(t_env *env)
{
	t_philo *philo;
	int status;
	pid_t *pid;
	int i;

	i = 0;
	env->start_sim = current_time();
	while (i < env->nu_philos)
	{
		philo = &env->philos[i];
		philo->start_sim = env->start_sim;
		philo->psid = fork();
		if (!philo->psid)
		{
			philo_routine(&env->philos[i]);
			exit(0);
		}
		i++;
	}
	i = 0;
	while (waitpid(-1, &status, 0))
	{
		if (status != 0)
		{
			kill_all(env->philos, env->nu_philos);
			destroy_sem(env);
			exit(1);
		}
	}
	return (NULL);
}