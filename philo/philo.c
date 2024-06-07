/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:57:56 by nhayoun           #+#    #+#             */
/*   Updated: 2024/06/07 18:40:42 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	main(int ac, char **av)
{
	t_env			env;
	int				correct_input;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];

	if ((ac == 5 || ac == 6) && check_args(ac, av))
	{
		env.philos = philos;
		env.forks = forks;
		init_data(ac, av, &env);
		simulation(&env);
	}
	return (0);
}
