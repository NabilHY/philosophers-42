/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:32:48 by nhayoun           #+#    #+#             */
/*   Updated: 2024/06/04 19:56:35 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_status(char state, unsigned long time, int id, t_philo *ph)
{
	pthread_mutex_lock(&ph->env->print);
	if (ph->env->end_sim == true)
	{
		pthread_mutex_unlock(&ph->env->print);
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
	pthread_mutex_unlock(&ph->env->print);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	{
		print_status('S', timestamp(philo->start_sim), philo->id, philo);
		usleep(500);
	}
	while (1)
	{
		print_status('T', timestamp(philo->start_sim), philo->id, philo);

		pthread_mutex_lock(&philo->rfork);
		print_status('F', timestamp(philo->start_sim), philo->id, philo);

		pthread_mutex_lock(&philo->lfork);
		print_status('F', timestamp(philo->start_sim), philo->id, philo);

		print_status('E', timestamp(philo->start_sim), philo->id, philo);
		pthread_mutex_lock(&philo->var);
		philo->last_eaten = current_time();
		pthread_mutex_unlock(&philo->var);
		suspend(philo->env->teat);

		pthread_mutex_unlock(&philo->rfork);
		pthread_mutex_unlock(&philo->lfork);

		print_status('S', timestamp(philo->start_sim), philo->id, philo);
		suspend(philo->env->tsleep);
	}
}

void	monitor(t_env *env)
{
	int		i;
	long	elapsed;
	t_philo	*philo;

	i = 0;
	while (i < env->nu_philos)
	{
		philo = &env->philos[i];
		pthread_mutex_lock(&philo->var);
		elapsed = current_time() - (philo->last_eaten);
		pthread_mutex_unlock(&philo->var);
		if (elapsed >= env->tdie)
		{
			print_status('D', env->philos[i].start_sim, env->philos[i].id,
				&env->philos[i]);
			exit(0);
		}
		i++;
		usleep(100);
	}
}

void	*simulation(t_env *env)
{
	int		i;
	t_philo	*philo;

	i = 0;
	env->start_sim = current_time();
	while (i < env->nu_philos)
	{
		philo = &env->philos[i];
		philo->start_sim = env->start_sim;
		philo->last_eaten = env->start_sim;
		if (pthread_create(&philo->thid, NULL, &routine, &env->philos[i]))
			handle_error("Thread Creation Failure !", 0);
		i++;
	}
	while (env->end_sim == false)
		monitor(env);
	i = 0;
	while (i < env->nu_philos)
	{
		philo = &env->philos[i];
		if (pthread_join(philo->thid, NULL))
			handle_error("Thread Exectution Failure !", 0);
		i++;
	}
	return (NULL);
}

/*
	To print the adaquate status we'll need
	the current time , the philosepher number and its state
	When a thread enters a routine
	He'll either
		Thinking : When they have finished eating
		and now waiting for the mutexes to be unlocked
		Eat : where both his fork and the target fork
		are free to use he'll do it by locking both the
		right and left mutexes
		Sleep : where he had finished execting (eating)
		then that thread enters stop executing
*/