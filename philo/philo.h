/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:58:00 by nhayoun           #+#    #+#             */
/*   Updated: 2024/06/05 16:32:49 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define FORMAT_ERR "Input Error\n"
#define PHILO_ERR "try something less than 200 philosephers\n"
#define MALLOC_ERR "MALLOC FAILURE"

typedef struct s_env	t_env;

typedef struct s_philo
{
	unsigned long		last_eaten;
	unsigned long		times_eaten;
	int					rfork;
	int					lfork;
	pthread_mutex_t		var;
	pthread_t			thid;
	unsigned long		start_sim;
	bool				full;
	int					id;
	t_env				*env;
}						t_philo;

typedef struct s_env
{
	unsigned long		tdie;
	unsigned long		teat;
	unsigned long		tsleep;
	unsigned long		nu_philos;
	unsigned long		meals_limit;
	unsigned long		start_sim;
	pthread_mutex_t		print;
	bool				end_sim;
	pthread_mutex_t		*forks;
	t_philo				*philos;
}						t_env;

int						_atoi(char *str);

int						valid_args(char **av, int ac);

void					*bytes_malloc(size_t bytes);

void					handle_error(char *str, int flag);

void					*simulation(t_env *env);

void					init_data(int ac, char **av, t_env *env);

unsigned long			current_time(void);

void					suspend(unsigned long ms);

unsigned long			timestamp(unsigned long start_time);
