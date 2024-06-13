/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:57:56 by nhayoun           #+#    #+#             */
/*   Updated: 2024/06/13 14:44:59 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	main(int ac, char **av)
{
	t_env			env;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];

	if ((ac == 5 || ac == 6) && check_args(ac, av))
	{
		env.philos = philos;
		env.forks = forks;
		init_data(ac, av, &env);
		if (!env.syscall_failure)
		{
			simulation(&env);
			destroy_mutexes(&env);
		}
		else
		{
			printf(SYSCALL_ERR);
			return (1);
		}
	}
	else if (ac != 5 || ac != 6)
		printf(ARG_ERR);
	return (0);
}
