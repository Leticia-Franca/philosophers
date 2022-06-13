/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 22:49:42 by lfranca-          #+#    #+#             */
/*   Updated: 2022/06/13 09:02:40 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_struct_philos(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->nb_philos)
	{
		program->philos[i].id_philo = i + 1;
		program->philos[i].left_fork = i;
		program->philos[i].right_fork = i + 1;
		program->philos[i].has_eaten = 0;
		program->philos[i].must_eat = program->nb_eat;
		program->philos[i].last_time_eaten = get_time();
		program->philos[i].program = program;
		if (i + 1 == program->nb_philos)
			program->philos[i].right_fork = 0;
		pthread_mutex_init(&program->forks[i], NULL);
		i++;
	}
}

int	init_struct_program(t_program *program, char **argv)
{
	program->nb_philos = ft_atoi(argv[1]);
	if (program->nb_philos < 1)
	{
		printf("Wrong number of philosophers.\n");
		return (1);
	}
	program->nb_forks = program->nb_philos;
	program->time_die = ft_atoi(argv[2]);
	program->time_eat = ft_atoi(argv[3]);
	program->time_sleep = ft_atoi(argv[4]);
	if(argv[5] != NULL)
		program->nb_eat = ft_atoi(argv[5]);
	else
		program->nb_eat = 0;
	program->forks = malloc(sizeof(pthread_mutex_t) * program->nb_philos);
	program->philos = malloc(sizeof(t_philo) * program->nb_philos);
	program->checker = 0;
	program->all_philos_ate = 0;
	pthread_mutex_init(&program->all_ate_checker, NULL);
	pthread_mutex_init(&program->meal_checker, NULL);
	init_struct_philos(program);
	return (0);
}
