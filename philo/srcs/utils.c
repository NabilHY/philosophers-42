/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:44:39 by nhayoun           #+#    #+#             */
/*   Updated: 2024/06/07 22:27:06 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	*sim_failure(t_env *env)
{
	env->syscall_failure = true;
	return (NULL);
}

int	_atoi(char *str)
{
	int		i;
	long	integer;
	int		sign;

	i = 0;
	integer = 0;
	sign = 1;
	while (str[i] <= 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		integer *= 10;
		integer += str[i] - '0';
		i++;
	}
	if (!str[i] && integer <= 2147483647 && sign == 1)
		return (integer);
	return (-1);
}

int	valid_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		if (_atoi(av[i]) == -1)
			return (0);
		if (av[i][j] == '+')
			j++;
		if (!isdigit(av[i][j]))
			return (0);
		while (av[i][j])
		{
			if (!isdigit(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_args(int ac, char **av)
{
	if (!valid_args(ac, av))
	{
		printf("%s\n", FORMAT_ERR);
		return (0);
	}
	if (_atoi(av[2]) < 60 || _atoi(av[3]) < 60 || _atoi(av[4]) < 60)
	{
		printf("%s\n", UNIT_ERR);
		return (0);
	}
	else if (_atoi(av[1]) > 200)
	{
		printf("%s\n", PHILO_ERR);
		return (0);
	}
	return (1);
}
