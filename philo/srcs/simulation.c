/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:32:48 by nhayoun           #+#    #+#             */
/*   Updated: 2024/06/12 16:50:50 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	completed(t_env *env)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = env->philos;
	while (i < env->nu_philos)
	{
		if (philos[i].full == false)
			return (0);
		i++;
	}
	return (1);
}

void	destroy_mutexes(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->nu_philos)
	{
		pthread_mutex_destroy(&env->forks[i]);
		i++;
	}
}

void	print_status(char state, int id, t_philo *ph)
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

void	suspend_even(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		print_status('S', philo->id, philo);
		suspend(philo->env->tsleep);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	suspend_even(philo);
	while ((!philo->env->end_sim) && philo->times_eaten != 0)
	{
		print_status('T', philo->id, philo);
		pthread_mutex_lock(&philo->env->forks[philo->lfork]);
		print_status('F', philo->id, philo);
		if (philo->env->nu_philos == 1)
			return (NULL);
		pthread_mutex_lock(&philo->env->forks[philo->rfork]);
		print_status('F', philo->id, philo);
		print_status('E', philo->id, philo);
		suspend(philo->env->teat);
		pthread_mutex_lock(&philo->time_update);
		philo->last_eaten = current_time();
		pthread_mutex_unlock(&philo->time_update);
		philo->times_eaten--;
		if (philo->times_eaten == 0)
			philo->full = true;
		pthread_mutex_unlock(&philo->env->forks[philo->lfork]);
		pthread_mutex_unlock(&philo->env->forks[philo->rfork]);
		print_status('S', philo->id, philo);
		suspend(philo->env->tsleep);
	}
	return (NULL);
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
			return (sim_failure(env));
		i++;
	}
	while (env->end_sim == false && !completed(env))
		monitor(env);
	i = 0;
	while (i < env->nu_philos)
	{
		philo = &env->philos[i];
		if (pthread_join(philo->thid, NULL))
			return (sim_failure(env));
		i++;
	}
	destroy_mutexes(env);
	return (NULL);
}
