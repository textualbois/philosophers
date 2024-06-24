/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_statements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:49:56 by isemin            #+#    #+#             */
/*   Updated: 2024/06/23 19:18:30 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_thinking(t_philosopher *philo)
{
	long	timestamp;

	time_stamp =
	printf("%ld %d is thinking\n", timestamp, philo->id);
}

void	print_taking_fork(t_philosopher *philo)
{
	long	timestamp;

	 = get_current_time_ms();
	printf("%ld %d has taken a fork\n", timestamp, philo->id);
}

void	print_eating(t_philosopher *philo)
{
	long	timestamp;

	 = get_current_time_ms();
	printf("%ld %d is eating\n", timestamp, philo->id);
}

void	print_sleeping(t_philosopher *philo)
{
	long	timestamp;

	 = get_current_time_ms();
	printf("%ld %d is sleeping\n", timestamp, philo->id);
}

void	print_death(t_philosopher *philo)
{
	long	timestamp;

	 = get_current_time_ms();
	printf("%ld %d died\n", timestamp, philo->id);
}