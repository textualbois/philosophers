/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_statements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivansemin <ivansemin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:49:56 by isemin            #+#    #+#             */
/*   Updated: 2024/06/24 01:50:57 by ivansemin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_thinking(t_philosopher *philo)
{
	long	timestamp;

	timestamp = time_from_start(philo->meta);
	printf("%ld %d is thinking\n", timestamp, philo->id);
}

void	print_taking_fork(t_philosopher *philo)
{
	long	timestamp;

	timestamp = time_from_start(philo->meta);
	printf("%ld %d has taken a fork\n", timestamp, philo->id);
}

void	print_eating(t_philosopher *philo)
{
	long	timestamp;

	timestamp = time_from_start(philo->meta);
	printf("%ld %d is eating\n", timestamp, philo->id);
}

void	print_sleeping(t_philosopher *philo)
{
	long	timestamp;

	timestamp = time_from_start(philo->meta);
	printf("%ld %d is sleeping\n", timestamp, philo->id);
}

void	print_death(t_philosopher *philo)
{
	long	timestamp;

	timestamp = time_from_start(philo->meta);
	printf("%ld %d died\n", timestamp, philo->id);
}
