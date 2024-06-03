/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:57:56 by nhayoun           #+#    #+#             */
/*   Updated: 2024/06/03 16:03:09 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

// T E S D

int	main(int ac, char **av)
{
	t_env			env;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];

	if ((ac == 5 || ac == 6) && valid_args(av, ac))
	{
		env.philos = philos;
		env.forks = forks;
		init_data(ac, av, &env);
		simulation(&env);
	}
	else
		printf("%s", FORMAT_ERR);
	return (0);
}

// ./philo 5 100 200 500 *5*f