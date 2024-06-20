/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:23:25 by nhayoun           #+#    #+#             */
/*   Updated: 2024/06/20 17:54:52 by nhayoun          ###   ########.fr       */
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
			//ph->env->end_sim = true;
			suspend(200);
			printf("%lu %u died\n", timestamp(ph->start_sim)-200, id);
			sem_post(ph->env->death);
			return ;
		}
	}
	sem_post(ph->env->print);
}

void	*monitor(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	while (!philo->env->end_sim)
	{
		//printf("id: %d elapsed %lu \n",philo->id, (current_time() - philo->last_eaten));
		sem_wait(philo->env->update_elapsed);
		if ((current_time() - philo->last_eaten) > philo->env->tdie)
		{
			print_status('D', philo->id, philo);
			break ;
		}
		sem_post(philo->env->update_elapsed);
	}
	return (NULL);
}

void	*philo_routine(t_philo *philo)
{
	//if (philo->id == philo->env->nu_philos)
	//{
	//	for (int i = 0; i < philo->env->nu_philos; i++)
	//		sem_post(philo->env->seated);
	//}
	//else
	//	sem_wait(philo->env->seated);
	sem_wait(philo->env->update_elapsed);
	philo->last_eaten = current_time();
	sem_post(philo->env->update_elapsed);
	if (pthread_create(&philo->thid, NULL, monitor, (void *)philo))
	{
		printf("Error creating thread!\n");
		exit(1);
	}
	philo->start_sim = philo->env->start_sim;
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
		sem_wait(philo->env->forks);
		print_status('F', philo->id, philo);
		sem_wait(philo->env->update_elapsed);
		philo->last_eaten = current_time();
		sem_post(philo->env->update_elapsed);
		philo->times_eaten--;
		print_status('E', philo->id, philo);
		suspend(philo->env->teat);
		sem_post(philo->env->forks);
		sem_post(philo->env->forks);
		print_status('S', philo->id, philo);
		suspend(philo->env->tsleep);
		if (philo->times_eaten == 0 && philo->id == philo->env->last_even)
			sem_post(philo->env->full);
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
	sem_close(env->full);
	sem_unlink(FULL);
	sem_close(env->death);
	sem_unlink(DEATH);
}

void	*food_monitor(void *arg)
{
	t_env	*env;
	int		i;

	i = 0;
	env = (t_env *)arg;
	sem_wait(env->full);
	destroy_sem(env);
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
	destroy_sem(env);
	kill_all(env->philos, env->nu_philos);
	exit(0);
	return (NULL);
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
		pthread_create(&env->death_monitor, NULL, &death_monitor, (void *)env);
		pthread_create(&env->food_monitor, NULL, &food_monitor, (void *)env);
		pthread_detach(env->death_monitor);
		pthread_detach(env->food_monitor);
		philo->psid = fork();
		if (!philo->psid)
		{
			philo_routine(&env->philos[i]);
			exit(0);
		}
		i++;
		//usleep(100);
	}

	while (waitpid(-1, &status, 0))
		;
	return (NULL);
}