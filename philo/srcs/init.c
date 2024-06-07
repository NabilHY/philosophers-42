/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:12:35 by nhayoun           #+#    #+#             */
/*   Updated: 2024/06/07 18:41:40 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_forks(pthread_mutex_t *forks, int forks_count)
{
	int	i;

	i = 0;
	while (i < forks_count)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			handle_error("Mutex Error\n", 0);
		i++;
	}
}

void	init_philos(t_env *env)
{
	int				i;
	t_philo			*philos;
	pthread_mutex_t	*forks;

	i = 0;
	philos = env->philos;
	forks = env->forks;
	while (i < env->nu_philos)
	{
		philos[i].full = false;
		philos[i].id = i + 1;
		philos[i].lfork = i;
		philos[i].rfork = (i + 1) % env->nu_philos;
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
	if (ac == 6)
		env->meals_limit = _atoi(av[5]);
	else
		env->meals_limit = -1;
	pthread_mutex_init(&env->print, NULL);
	pthread_mutex_init(&env->update_elapsed, NULL);
}

void	init_data(int ac, char **av, t_env *env)
{
	int	i;

	i = 0;
	init_env(env, av, ac);
	init_forks(env->forks, env->nu_philos);
	init_philos(env);
}
