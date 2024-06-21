/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:23:25 by nhayoun           #+#    #+#             */
/*   Updated: 2024/06/21 22:47:47 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

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
		else if (state == 'D' && ph->times_eaten != 0)
		{
			ph->env->end_sim = true;
			printf("%lu %u died\n", timestamp(ph->start_sim), id);
			sem_post(ph->env->death);
			return ;
		}
	}
	sem_post(ph->env->print);
}

void	eating(t_philo *philo)
{
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
}

void	*philo_routine(t_philo *philo)
{
	sem_wait(philo->env->update_elapsed);
	philo->last_eaten = current_time();
	sem_post(philo->env->update_elapsed);
	pthread_create(&philo->thid, NULL, monitor, (void *)philo);
	philo->start_sim = philo->env->start_sim;
	if (philo->id % 2 == 0)
	{
		print_status('S', philo->id, philo);
		suspend(philo->env->tsleep);
	}
	while (1)
	{
		if (philo->times_eaten == 0 && philo->id == philo->env->last_even)
		{
			sem_post(philo->env->full);
			break;
		}
		if (philo->env->end_sim)
			break;
		print_status('T', philo->id, philo);
		eating(philo);
		print_status('S', philo->id, philo);
		suspend(philo->env->tsleep);
	}
	pthread_join(philo->thid, NULL);
	return (NULL);
}

void	*simulation(t_env *env)
{
	t_philo	*philo;
	int		status;
	pid_t	*pid;
	int		i;

	i = 0;
	env->start_sim = current_time();
	pthread_create(&env->death_monitor, NULL, &death_monitor, (void *)env);
	pthread_create(&env->food_monitor, NULL, &food_monitor, (void *)env);
	while (i < env->nu_philos)
	{
		philo = &env->philos[i];
		philo->psid = fork();
		if (!philo->psid)
		{
			philo_routine(&env->philos[i]);
			exit(0);
		}
		i++;
	}
	while (waitpid(-1, &status, 0))
		;
	pthread_join(env->death_monitor, NULL);
	pthread_join(env->food_monitor, NULL);
	return (NULL);
}
