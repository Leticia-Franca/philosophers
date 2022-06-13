/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 19:21:41 by lfranca-          #+#    #+#             */
/*   Updated: 2022/06/13 08:59:13 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_program t_program;

typedef struct s_philo
{
	int				id_philo;
	int				right_fork;
	int				left_fork;
	int				has_eaten;
	int				must_eat;
	long long int	last_time_eaten;
	t_program		*program;
	pthread_t		thread;
}				t_philo;

struct s_program
{
	int				nb_philos;
	int				nb_forks;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_eat;
	int				checker;
	int				all_philos_ate;
	long long int	time_simulation_start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	all_ate_checker;
	pthread_mutex_t	meal_checker; //
	pthread_t		death_monitor;
	t_philo			*philos;
};

int				ft_atoi(const char *nptr);
void			init_struct_philos(t_program *program);
int				init_struct_program(t_program *program, char **argv);
void			create_threads(t_program *program);
long long int	get_time(void);
void			*routine(void *data);
void			*has_died(void *param);
void			print_philo_state(long long int time, char *state, t_philo *philo);
void			lock_and_print(t_program *prog, char *msg, t_philo *philo);

#endif