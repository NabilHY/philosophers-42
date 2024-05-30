/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:12:35 by nhayoun           #+#    #+#             */
/*   Updated: 2024/05/30 16:23:19 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		handle_error("Error Occured\n", 0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	*routine(void)
{
	// pthread_mutex_lock(&print);
	printf("Routini lyawmi\n");
	// pthread_mutex_unlock(&print);
	return (NULL);
}

void	init_philos(t_env *env)
{
	int				i;
	t_philo			**philos;
	pthread_mutex_t	**forks;

	i = 0;
	philos = &env->philos;
	forks = &env->forks;
	while (i < env->nu_philos)
	{
		philos[i]->full = false;
		philos[i]->id = i + 1;
		if (pthread_create(&philos[i], NULL, &routine, NULL))
			handle_error("Thread Creation Error\n", 0);
		philos[i]->rfork = 
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
		if (pthread_mutex_init(&forks[i], NULL))
			handle_error("Mutex Error\n", 0);
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
}

void	init_data(int ac, char **av, t_env *env)
{
	int i;

	i = 0;
	init_env(env, av, ac);
	init_forks(env->forks, env->nu_philos);
	init_philos(env);
}