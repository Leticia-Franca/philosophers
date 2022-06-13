/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_died.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 22:50:35 by lfranca-          #+#    #+#             */
/*   Updated: 2022/06/13 09:27:05 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	lock_and_print(t_program *prog, char *msg, t_philo *philo)
{
	pthread_mutex_lock(&prog->meal_checker);
	print_philo_state(get_time(), msg, philo);
	pthread_mutex_unlock(&prog->meal_checker);
}

static int	is_dead(t_program *program, int i)
{
	pthread_mutex_lock(&program->meal_checker);
	print_philo_state(get_time(), "died", &program->philos[i]);
	program->checker = 1;
	pthread_mutex_unlock(&program->meal_checker);
	if (program->nb_eat == 0)
		return (1);
	return (0);
}

static int	change_all_ate(t_program *program, int i)
{
	if (i == program->nb_philos)
	{
		pthread_mutex_lock(&program->all_ate_checker);
		program->all_philos_ate = 1;
		pthread_mutex_unlock(&program->all_ate_checker);
		return (1);
	}
	return (0);
}

static int	count_who_ate(t_program *program)
{
	int	i;

	i = 0;
	while (program->nb_eat > 0 && i < program->nb_philos)
	{
		pthread_mutex_lock(&program->all_ate_checker); //pode mudar isso pra criar outro mutex
		if (program->philos[i].has_eaten >= program->nb_eat)
			i++;
		pthread_mutex_unlock(&program->all_ate_checker);
	}
	if (change_all_ate(program, i) == 1)
		return (1);
	return (0);
}

void	*has_died(void *param)
{
	t_program	*program;
	int			i;

	program = param;
	pthread_mutex_lock(&program->all_ate_checker);
	while (program->all_philos_ate != 1)
	{
		pthread_mutex_unlock(&program->all_ate_checker);
		i = -1;
		pthread_mutex_lock(&program->meal_checker);
		while (++i < program->nb_philos && program->checker != 1)
		{
			pthread_mutex_unlock(&program->meal_checker);
			pthread_mutex_lock(&program->meal_checker);
			if (get_time() - program->philos[i].last_time_eaten > program->time_die)
			{
				pthread_mutex_unlock(&program->meal_checker);
				if (is_dead(program, i) == 1)
					return (NULL);
				usleep(1000);
			}
			else
				continue;
			pthread_mutex_lock(&program->meal_checker);
		}
		pthread_mutex_unlock(&program->meal_checker);
		if (program->checker == 1)
			return (NULL);
		if (count_who_ate(program) == 1)
			return (NULL);
		pthread_mutex_lock(&program->all_ate_checker);
	}
	//pthread_mutex_unlock(&program->all_ate_checker);
	return (NULL);
}
// ABAIXO DO NULL::
//	i = -1;
	// while (++i < program->nb_philos)
	// {
	// 	if (program->nb_eat == 0
	// 		&& get_time() - program->philos[i].last_time_eaten > program->time_die)
	// 	{
	// 		pthread_mutex_lock(&program->meal_checker);
	// 		print_philo_state(get_time(), "died", &program->philos[i]);
	// 		program->checker = 1;
	// 		pthread_mutex_unlock(&program->meal_checker);
	// 		return (NULL);
	// 	}
	// 	if (program->nb_eat > 0 && program->philos[i].has_eaten == program->nb_eat)
	// 		program->all_philos_ate++;
	// 	if (program->all_philos_ate == program->nb_philos)
	// 	{
	// 		pthread_mutex_lock(&program->meal_checker);
	// 		program->checker = 1;
	// 		pthread_mutex_unlock(&program->meal_checker);
	// 		return (NULL);
	// 	}
	// 	if (i + 1 == program->nb_philos)
	// 		i = -1;
	// 	usleep(150);
	// }
