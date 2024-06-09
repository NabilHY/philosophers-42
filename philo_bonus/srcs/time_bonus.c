/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:25:48 by nhayoun           #+#    #+#             */
/*   Updated: 2024/06/08 16:26:20 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

unsigned long	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	suspend(unsigned long ms)
{
	unsigned long	start_time;
	unsigned long	expected_time;

	start_time = current_time();
	expected_time = start_time + ms;
	while (current_time() < expected_time)
		usleep(200);
}

unsigned long	timestamp(unsigned long start_time)
{
	return (current_time() - start_time);
}