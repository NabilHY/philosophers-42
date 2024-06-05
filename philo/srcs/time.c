/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:54:17 by nhayoun           #+#    #+#             */
/*   Updated: 2024/06/05 20:00:56 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

unsigned long	current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		handle_error("Error Occured\n", 0);
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
