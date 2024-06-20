/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:19:48 by nhayoun           #+#    #+#             */
/*   Updated: 2024/06/18 19:48:28 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	init_philos(t_env *env)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = env->philos;
	while (i < env->nu_philos)
	{
		philos[i].id = i + 1;
		philos[i].env = env;
		philos[i].start_sim = env->start_sim;
		if (env->meals_limit == -1)
			philos[i].times_eaten = -1;
		else
			philos[i].times_eaten = env->meals_limit;
		i++;
	}
}

int last_even(int number)
{
	if (number % 2 == 0)
		return (number);
	return (number - 1);
}

void	init_env(t_env *env, char **av, int ac)
{
	env->start_sim = 0;
	env->nu_philos = _atoi(av[1]);
	env->tdie = _atoi(av[2]);
	env->teat = _atoi(av[3]);
	env->tsleep = _atoi(av[4]);
	env->end_sim = false;
	env->syscall_failure = false;
	env->last_even = last_even(env->nu_philos);
	env->start_sim = current_time();
	if (ac == 6)
		env->meals_limit = _atoi(av[5]);
	else
		env->meals_limit = -1;
	sem_unlink(FORKS);
	env->forks = sem_open(FORKS, O_CREAT, 0777, env->nu_philos);
	sem_unlink(PRINT);
	env->print = sem_open(PRINT, O_CREAT, 0777, 1);
	sem_unlink(ELAPSED);
	env->update_elapsed = sem_open(ELAPSED, O_CREAT, 0777, 1);
	sem_unlink(SEATED);
	env->seated = sem_open(SEATED, O_CREAT, 0644, 0);
	sem_unlink(DEATH);
	env->death = sem_open(DEATH, O_CREAT, 0644, 0);
	sem_unlink(FULL);
	env->full = sem_open(FULL, O_CREAT, 0644, 0);
	sem_unlink(ENTRY);
	env->entry = sem_open(ENTRY, O_CREAT, 0644, 0);
}

void	init_data(int ac, char **av, t_env *env)
{
	int i;

	i = 0;
	init_env(env, av, ac);
	init_philos(env);
}