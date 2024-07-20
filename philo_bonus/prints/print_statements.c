/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_statements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:49:56 by isemin            #+#    #+#             */
/*   Updated: 2024/07/20 04:46:26 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_thinking(t_philosopher *philo)
{
	int	timestamp;

	timestamp = time_from_start(philo->meta);
	printf("%d %d is thinking\n", timestamp, philo->id);
}

void	print_taking_fork(t_philosopher *philo)
{
	int	timestamp;

	timestamp = time_from_start(philo->meta);
	printf("%d %d has taken a fork\n", timestamp, philo->id);
}

void	print_eating(t_philosopher *philo)
{
	int	timestamp;

	timestamp = time_from_start(philo->meta);
	printf("%d %d is eating\n", timestamp, philo->id);
}

void	print_sleeping(t_philosopher *philo)
{
	int	timestamp;

	timestamp = time_from_start(philo->meta);
	printf("%d %d is sleeping\n", timestamp, philo->id);
}

void	print_death(t_philosopher *philo)
{
	int	timestamp;

	timestamp = time_from_start(philo->meta);
	printf("%d %d died\n", timestamp, philo->id);
}
