/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:57:56 by nhayoun           #+#    #+#             */
/*   Updated: 2024/06/05 19:59:35 by nhayoun          ###   ########.fr       */
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
/*
	Do not test with more than 200 philosophers.
Do not test with time_to_die or time_to_eat or time_to_sleep set to values lower than 60 ms.
Test 1 800 200 200. The philosopher should not eat and should die.
Test 5 800 200 200. No philosopher should die.
Test 5 800 200 200 7. No philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times.
Test 4 410 200 200. No philosopher should die.
Test 4 310 200 100. One philosopher should die.
Test with 2 philosophers and check the different times: a death delayed by more than 10 ms is unacceptable.
Test with any values of your choice to verify all the requirements. Ensure philosophers die at the right time,
	that they don't steal forks, and so forth.
*/