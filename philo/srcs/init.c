/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:12:35 by nhayoun           #+#    #+#             */
/*   Updated: 2024/05/29 20:44:29 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

pthread_mutex_t	print;

void	*routine(void)
{
	//pthread_mutex_lock(&print);
	printf("Routini lyawmi\n");
	//pthread_mutex_unlock(&print);
	return (NULL);
}

void	init_philos(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->nu_philos)
	{
		env->philos[i].full = false;
		env->philos[i].id = i + 1;
		env->philos[i].last_eaten
		pthread_create(&env->philos[i], NULL, &routine, NULL);
		i++;
	}
	i = 0;
}

void	init_forks(pthread_mutex_t *forks, int forks_count)
{
	int	i;

	i = 0;
	while (i < forks_count)
	{
		pthread_mutex_init(&forks[i], NULL);
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
	env->end_sim = 0;
	env->meals_limit = -1;
	if (ac == 6)
		env->meals_limit = _atoi(av[5]);
	env->start_sim = (long)time(NULL);
}

void	init_data(int ac, char **av, t_env *env)
{
	int i;

	i = 0;
	init_env(env, av, ac);
	init_forks(env->forks, env->nu_philos);
	init_philos(env);
}