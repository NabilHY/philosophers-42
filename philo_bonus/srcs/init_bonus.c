/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:19:48 by nhayoun           #+#    #+#             */
/*   Updated: 2024/06/09 19:55:07 by nhayoun          ###   ########.fr       */
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
		if (env->meals_limit == -1)
			philos[i].times_eaten = -1;
		else
			philos[i].times_eaten = env->meals_limit;
		i++;
	}
}

void	init_env(t_env *env, char **av, int ac)
{
	env->nu_philos = _atoi(av[1]);
	env->tdie = _atoi(av[2]);
	env->teat = _atoi(av[3]);
	env->tsleep = _atoi(av[4]);
	env->start_sim = 0;
	env->end_sim = false;
	env->syscall_failure = false;
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
	env->seated = sem_open(SEATED, O_CREAT, 0777, env->nu_philos);
}

void	init_data(int ac, char **av, t_env *env)
{
	int i;

	i = 0;
	init_env(env, av, ac);
	init_philos(env);
}