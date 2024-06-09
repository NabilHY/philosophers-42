/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:54:10 by nhayoun           #+#    #+#             */
/*   Updated: 2024/06/09 18:44:17 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>

#define FORMAT_ERR "Input Error\n"
#define PHILO_ERR "Try something less than 200 philosephers\n"
#define UNIT_ERR "Test with values greater than 60ms"
#define SYSCALL_ERR "One of the syscall funtions has failed!"
#define FORKS "/forks"
#define PRINT "/print"
#define ELAPSED "/elapsed"
#define SEATED "/seated"

typedef struct s_env	t_env;

typedef struct s_philo
{
	unsigned long		last_eaten;
	unsigned long		times_eaten;
	unsigned long		start_sim;
	int					rfork;
	int					lfork;
	int					id;
	pid_t				psid;
	t_env				*env;
	pthread_t			thid;
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
	bool				end_sim;
	t_philo				*philos;
	sem_t				*update_elapsed;
	sem_t				*forks;
	sem_t				*print;
	sem_t				*seated;
}						t_env;

int						_atoi(char *str);

void					init_data(int ac, char **av, t_env *env);

int						check_args(int ac, char **av);

unsigned long			current_time(void);

unsigned long			timestamp(unsigned long start_time);

//void					monitor(t_env *env);

void					print_status(char state, int id, t_philo *ph);

void					*simulation(t_env *env);

void					suspend(unsigned long ms);