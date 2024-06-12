/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:58:00 by nhayoun           #+#    #+#             */
/*   Updated: 2024/06/12 16:31:28 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define FORMAT_ERR "Input Error\n"
#define PHILO_ERR "Try something less than 200 philosephers\n"
#define UNIT_ERR "Test with values greater than 60ms"
#define SYSCALL_ERR "One of the syscall funtions has failed!"

typedef struct s_env	t_env;

typedef struct s_philo
{
	unsigned long		last_eaten;
	unsigned long		times_eaten;
	pthread_mutex_t		time_update;
	unsigned long		start_sim;
	pthread_t			thid;
	t_env				*env;
	bool				full;
	int					rfork;
	int					lfork;
	int					id;
}						t_philo;

typedef struct s_env
{
	bool				correct_input;
	bool				syscall_failure;
	unsigned long		tdie;
	unsigned long		teat;
	unsigned long		tsleep;
	unsigned long		nu_philos;
	unsigned long		meals_limit;
	unsigned long		start_sim;
	pthread_mutex_t		update_elapsed;
	pthread_mutex_t		print;
	bool				end_sim;
	pthread_mutex_t		*forks;
	t_philo				*philos;
}						t_env;

int						_atoi(char *str);

void					*sim_failure(t_env *env);

void					*simulation(t_env *env);

void					init_data(int ac, char **av, t_env *env);

unsigned long			current_time(void);

void					suspend(unsigned long ms);

unsigned long			timestamp(unsigned long start_time);

int						check_args(int ac, char **av);

void					monitor(t_env *env);

int						threads_full(t_env *env);

void					print_status(char state, int id, t_philo *ph);
