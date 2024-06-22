/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:53:38 by nhayoun           #+#    #+#             */
/*   Updated: 2024/06/22 21:01:39 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_env	env;
	t_philo	philos[200];

	if ((ac == 5 || ac == 6) && check_args(ac, av))
	{
		env.philos = philos;
		init_data(ac, av, &env);
		simulation(&env);
		return (0);
	}
}
