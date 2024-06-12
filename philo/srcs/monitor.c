/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:07:57 by nhayoun           #+#    #+#             */
/*   Updated: 2024/06/12 16:27:39 by nhayoun          ###   ########.fr       */
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
	int				i;
	unsigned long	elapsed;
	t_philo			*philo;

	i = 0;
	while (i < env->nu_philos && env->end_sim == false)
	{
		philo = &env->philos[i];
		pthread_mutex_lock(&philo->time_update);
		elapsed = current_time() - (philo->last_eaten);
		pthread_mutex_unlock(&philo->time_update);
		if (elapsed > env->tdie)
		{
			print_status('D', env->philos[i].id, &env->philos[i]);
			env->end_sim = true;
			return ;
		}
		i++;
	}
}
