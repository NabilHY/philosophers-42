/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:32:48 by nhayoun           #+#    #+#             */
/*   Updated: 2024/06/03 18:49:59 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

unsigned long	current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		handle_error("Error Occured\n", 0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	suspend(unsigned long ms)
{
	unsigned long	start_time;
	unsigned long	expected_time;

	start_time = current_time();
	expected_time = start_time + ms;
	while (current_time() < expected_time)
		usleep(200);
}

unsigned long	timestamp(unsigned long start_time)
{
	return (current_time() - start_time);
}

void	print_status(char state, unsigned long time, int id, t_philo *ph)
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
		printf("%lu %u died\n", timestamp(ph->start_sim), id);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	{
		print_status('S', timestamp(philo->start_sim), philo->id, philo);
		suspend(philo->env->tsleep);
	}
	while (1)
	{
		print_status('T', timestamp(philo->start_sim), philo->id, philo);
		pthread_mutex_lock(philo->rfork);
		print_status('F', timestamp(philo->start_sim), philo->id, philo);
		pthread_mutex_lock(philo->lfork);
		print_status('F', timestamp(philo->start_sim), philo->id, philo);
		philo->last_eaten = current_time();
		print_status('E', timestamp(philo->start_sim), philo->id, philo);
		suspend(philo->env->teat);
		pthread_mutex_unlock(philo->lfork);
		pthread_mutex_unlock(philo->rfork);
		print_status('S', timestamp(philo->start_sim), philo->id, philo);
		suspend(philo->env->tsleep);
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
		philo = env->philos + i;
		philo->start_sim = env->start_sim;
		if (pthread_create(philo->thid, NULL, &routine, philo))
			handle_error("Thread Creation Failure !", 0);
		i++;
	}
	i = 0;
	while (i < env->nu_philos)
	{
		philo = env->philos + i;
		if (pthread_join(philo , NULL))
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