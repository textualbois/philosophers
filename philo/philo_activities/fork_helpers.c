/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 01:23:42 by isemin            #+#    #+#             */
/*   Updated: 2024/07/19 23:39:29 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pick_up_from_left(t_philosopher *philo)
{
	if (pthread_mutex_lock(philo->left_fork->mutex) != 0)
		return (-1);
	pthread_mutex_lock(philo->meta->global_mtx);
	print_action(TAKING_FORK, philo);
	pthread_mutex_unlock(philo->meta->global_mtx);
	if (philo->right_fork == philo->left_fork)
	{
		pthread_mutex_unlock(philo->left_fork->mutex);
		return (-1);
	}
	pthread_mutex_lock(philo->right_fork->mutex);
	pthread_mutex_lock(philo->meta->global_mtx);
	print_action(TAKING_FORK, philo);
	pthread_mutex_unlock(philo->meta->global_mtx);
	return (0);
}

int	pick_up_from_right(t_philosopher *philo)
{
	if (pthread_mutex_lock(philo->right_fork->mutex) != 0)
		return (-1);
	pthread_mutex_lock(philo->meta->global_mtx);
	print_action(TAKING_FORK, philo);
	pthread_mutex_unlock(philo->meta->global_mtx);
	if (philo->right_fork == philo->left_fork)
	{
		pthread_mutex_unlock(philo->right_fork->mutex);
		return (-1);
	}
	pthread_mutex_lock(philo->meta->global_mtx);
	print_action(TAKING_FORK, philo);
	pthread_mutex_unlock(philo->meta->global_mtx);
	return (0);
}
