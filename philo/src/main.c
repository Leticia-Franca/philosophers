/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:24:26 by lfranca-          #+#    #+#             */
/*   Updated: 2022/06/13 08:51:53 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	error_args(void)
{
	printf("Wrong number of arguments. Please, insert 5 or 6 arguments.\n");
	return (EXIT_FAILURE);
}

void	create_philo(t_program *program)
{
	int i;

	i = -1;
	while (++i < program->nb_philos)
		pthread_create(&program->philos[i].thread, NULL, &routine, &program->philos[i]);
}

int	main(int argc, char **argv)
{
	t_program		program;
	int				i;

	i = -1;
	if (argc < 5 || argc > 6)
		exit(error_args());
	pthread_mutex_init(&program.print, NULL);
	pthread_mutex_init(&program.meal_checker, NULL);
	program.time_simulation_start = get_time();
	if (init_struct_program(&program, argv) == 1)
	{
		pthread_mutex_destroy(&program.print);
		exit(1);
	}
	create_philo(&program);
	pthread_create(&program.death_monitor, NULL, &has_died, &program);
	while (++i < program.nb_philos)
		pthread_join(program.philos[i].thread, NULL);
	pthread_join(program.death_monitor, NULL);
	i = -1;
	while (++i < program.nb_philos)
		pthread_mutex_destroy(&program.forks[i]);
	pthread_mutex_destroy(&program.print);
	free(program.philos);
	free(program.forks);
	return (0);
}