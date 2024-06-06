/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:07:57 by nhayoun           #+#    #+#             */
/*   Updated: 2024/06/06 16:26:47 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	threads_full(t_env *env)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = env->philos;
	while (i < env->nu_philos)
	{
		if (philos[i].times_eaten != 0)
			return (0);
		i++;
	}
	return (1);
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
		pthread_mutex_lock(&env->update_elapsed);
		elapsed = current_time() - (philo->last_eaten);
		pthread_mutex_unlock(&env->update_elapsed);
		if (elapsed > env->tdie)
		{
			print_status('D', env->philos[i].start_sim, env->philos[i].id,
				&env->philos[i]);
			env->end_sim = true;
			return ;
		}
		i++;
	}
}
