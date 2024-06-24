/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:54:10 by nhayoun           #+#    #+#             */
/*   Updated: 2024/06/24 11:49:23 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define FORMAT_ERR "Input Error\n"
#define PHILO_ERR "Try something less than 200 philosephers\n"
#define UNIT_ERR "Test with values greater than 60ms"
#define SYSCALL_ERR "One of the syscall funtions has failed!"
#define FORKS "/forks"
#define PRINT "/print"
#define ELAPSED "/elapsed"
#define SEATED "/seated"
#define END_SIM "/end_sim"
#define DEATH "/death"
#define FULL "/full"
#define ENTRY "/entry"
#define EXIT "/exit"
#define SIM "/sim"

typedef struct s_env	t_env;

typedef struct s_philo
{
	unsigned long		last_eaten;
	unsigned long		times_eaten;
	unsigned long		start_sim;
	pid_t				psid;
	t_env				*env;
	pthread_t			thid;
	int					rfork;
	int					lfork;
	int					id;
}						t_philo;

typedef struct s_env
{
	unsigned long		tdie;
	unsigned long		teat;
	unsigned long		tsleep;
	unsigned long		nu_philos;
	unsigned long		meals_limit;
	unsigned long		start_sim;
	pthread_t			death_monitor;
	pthread_t			food_monitor;
	t_philo				*philos;
	sem_t				*update_elapsed;
	sem_t				*forks;
	sem_t				*print;
	sem_t				*death;
	sem_t				*full;
	bool				correct_input;
	bool				syscall_failure;
	bool				end_sim;
	int					last_even;
}						t_env;

int						_atoi(char *str);

void					init_data(int ac, char **av, t_env *env);

int						check_args(int ac, char **av);

unsigned long			current_time(void);

unsigned long			timestamp(unsigned long start_time);

int						last_even(int number);

void					print_status(char state, int id, t_philo *ph);

void					*simulation(t_env *env);

void					suspend(unsigned long ms);

void					*food_monitor(void *arg);

void					*death_monitor(void *arg);

void					*monitor(void *arg);

void					kill_all(t_philo *philos, int philos_nu);

void					destroy_sem(t_env *env);
