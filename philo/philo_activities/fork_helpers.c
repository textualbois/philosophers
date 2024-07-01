/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 01:23:42 by isemin            #+#    #+#             */
/*   Updated: 2024/07/01 12:04:23 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	pick_up_forks(t_philosopher *philo)
// {
// 	if (philo->order == ODD_NUMBER)
// 	{å
// 		pthread_mutex_lock(philo->left_fork->mutex);
// 		pthread_mutex_lock(philo->meta->global_mtx);
// 		print_action(TAKING_FORK, philo);
// 		pthread_mutex_unlock(philo->meta->global_mtx);
// 	}
// 	else if (philo->times_eaten == 0)
// 	{
// 		sleep_ms(philo->meta->time_to_eat / 2);
// 	}

// 	pthread_mutex_lock(philo->right_fork->mutex);
// 	pthread_mutex_lock(philo->meta->global_mtx);
// 	print_action(TAKING_FORK, philo);
// 	pthread_mutex_unlock(philo->meta->global_mtx);

// 	if (philo->order != ODD_NUMBER)
// 	{
// 		pthread_mutex_lock(philo->left_fork->mutex);
// 		pthread_mutex_lock(philo->meta->global_mtx);
// 		print_action(TAKING_FORK, philo);
// 		pthread_mutex_unlock(philo->meta->global_mtx);
// 	}
// }

void	pick_up_from_left(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left_fork->mutex);
	pthread_mutex_lock(philo->meta->global_mtx);
	print_action(TAKING_FORK, philo);
	pthread_mutex_unlock(philo->meta->global_mtx);

	pthread_mutex_lock(philo->right_fork->mutex);
	pthread_mutex_lock(philo->meta->global_mtx);
	print_action(TAKING_FORK, philo);
	pthread_mutex_unlock(philo->meta->global_mtx);
}

void	pick_up_from_right(t_philosopher *philo)
{
	pthread_mutex_lock(philo->right_fork->mutex);
	pthread_mutex_lock(philo->meta->global_mtx);
	print_action(TAKING_FORK, philo);
	pthread_mutex_unlock(philo->meta->global_mtx);

	pthread_mutex_lock(philo->left_fork->mutex);
	pthread_mutex_lock(philo->meta->global_mtx);
	print_action(TAKING_FORK, philo);
	pthread_mutex_unlock(philo->meta->global_mtx);
}
