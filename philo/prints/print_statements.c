/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_statements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:49:56 by isemin            #+#    #+#             */
/*   Updated: 2024/07/23 17:38:34 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_thinking(t_philosopher *philo, pthread_mutex_t *print_lock)
{
	int	timestamp;

//	pthread_mutex_lock(print_lock);
	timestamp = time_from_start(philo->meta);
	printf("%d %d is thinking\n", timestamp, philo->id);
	allowed_to_continue(0, 0, RELEASE_LOCK);
	pthread_mutex_unlock(print_lock);
}

void	print_taking_fork(t_philosopher *philo, pthread_mutex_t *print_lock)
{
	int	timestamp;

	//pthread_mutex_lock(print_lock);
	timestamp = time_from_start(philo->meta);
	printf("%d %d has taken a fork\n", timestamp, philo->id);
	allowed_to_continue(0, 0, RELEASE_LOCK);
	pthread_mutex_unlock(print_lock);
}

void	print_eating(t_philosopher *philo, pthread_mutex_t *print_lock)
{
	int	timestamp;

//	pthread_mutex_lock(print_lock);
	timestamp = time_from_start(philo->meta);
	printf("%d %d is eating\n", timestamp, philo->id);
	allowed_to_continue(0, 0, RELEASE_LOCK);
	pthread_mutex_unlock(print_lock);
}

void	print_sleeping(t_philosopher *philo, pthread_mutex_t *print_lock)
{
	int	timestamp;

//pthread_mutex_lock(print_lock);
	timestamp = time_from_start(philo->meta);
	printf("%d %d is sleeping\n", timestamp, philo->id);
	allowed_to_continue(0, 0, RELEASE_LOCK);
	pthread_mutex_unlock(print_lock);
}

void	print_death(t_philosopher *philo, pthread_mutex_t *print_lock)
{
	int	timestamp;

//	pthread_mutex_lock(print_lock);
	timestamp = time_from_start(philo->meta);
	printf("%d %d died\n", timestamp, philo->id);
	allowed_to_continue(0, 0, RELEASE_LOCK);
	pthread_mutex_unlock(print_lock);
}
