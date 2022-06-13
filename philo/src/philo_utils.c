/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:31:07 by lfranca-          #+#    #+#             */
/*   Updated: 2022/06/13 08:59:15 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_atoi(const char *nptr)
{
	int	value;
	int	sign;
	int	i;

	i = 0;
	value = 0;
	sign = 1;
	while (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\v'
		|| nptr[i] == '\t' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		value = value * 10 + (nptr[i] - '0');
		i++;
	}
	return (value * sign);
}

long long int	get_time(void)
{
	struct timeval	tv;
	long long int	time_milliscds;

	gettimeofday(&tv, NULL);
	time_milliscds = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time_milliscds);
}

void	print_philo_state(long long int time, char *state, t_philo *philo)
{
	// long long int	sim_start;

	// sim_start = philo->program->time_simulation_start;
	pthread_mutex_lock(&philo->program->print);
	if (philo->program->checker != 1)
		printf("%5lld %d %s\n", time - philo->program->time_simulation_start, philo->id_philo, state);
	pthread_mutex_unlock(&philo->program->print);
}
