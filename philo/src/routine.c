/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 23:32:29 by lfranca-          #+#    #+#             */
/*   Updated: 2022/06/13 09:35:37 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	single_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->forks[philo->right_fork]);
	print_philo_state(get_time(), "has taken a fork", philo);
	pthread_mutex_unlock(&philo->program->forks[philo->right_fork]);
	print_philo_state(get_time(), "died", philo);
	pthread_mutex_lock(&philo->program->meal_checker);
	philo->last_time_eaten = get_time();
	philo->program->checker = 1;
	pthread_mutex_unlock(&philo->program->meal_checker);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->forks[philo->left_fork]);
	pthread_mutex_lock(&philo->program->forks[philo->right_fork]);
	lock_and_print(philo->program, "has taken a fork", philo);
	lock_and_print(philo->program, "has taken a fork", philo);
	pthread_mutex_lock(&philo->program->meal_checker);
	print_philo_state(get_time(), "is eating", philo);
	philo->last_time_eaten = get_time();
	pthread_mutex_lock(&philo->program->all_ate_checker);
	philo->has_eaten++;
	pthread_mutex_unlock(&philo->program->meal_checker);
	pthread_mutex_unlock(&philo->program->all_ate_checker);
	usleep(philo->program->time_eat * 1000);
	pthread_mutex_unlock(&philo->program->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->program->forks[philo->right_fork]);
}

static int	did_they_eat_all(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->all_ate_checker);
	if (philo->program->all_philos_ate == 1)
	{
		pthread_mutex_unlock(&philo->program->all_ate_checker);
		return (1);
	}
	pthread_mutex_unlock(&philo->program->all_ate_checker);
	return (0);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = data;
	if (philo->program->nb_philos == 1)
	{
		single_philo(philo);
		return (NULL);
	}
	if (philo->id_philo % 2 == 0)
		usleep(2000);
	pthread_mutex_lock(&philo->program->meal_checker);
	while (philo->program->checker != 1)
	{
		pthread_mutex_unlock(&philo->program->meal_checker);
		eat(philo);
		if (did_they_eat_all(philo) == 1)
			return (NULL);
		lock_and_print(philo->program, "is sleeping", philo);
		usleep(philo->program->time_sleep * 1000);
		lock_and_print(philo->program, "is thinking", philo);
		pthread_mutex_lock(&philo->program->meal_checker);
	}
	pthread_mutex_unlock(&philo->program->meal_checker);
	return (NULL);
}


// pthread_mutex_lock(&philo->program->all_ate_checker);
// if (philo->program->all_philos_ate == 1)
// {
// 	pthread_mutex_unlock(&philo->program->all_ate_checker);
// 	break ;
// }
// pthread_mutex_unlock(&philo->program->all_ate_checker);
