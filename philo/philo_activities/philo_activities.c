/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivansemin <ivansemin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 01:55:21 by ivansemin         #+#    #+#             */
/*   Updated: 2024/06/26 16:30:59 by ivansemin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philosopher *philo)
{
	// printf("philo in think\n");
	print_action(THINKING, philo);
}

void	pick_up_forks(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		// printf("philo %i wants to do an action\n", philo->id);
		//pthread_mutex_lock(philo->meta->global_mtx); // signal watcher that you want to perform an action
		pthread_mutex_lock(philo->left_fork->mutex); // get in queue to get a fork
		pthread_mutex_lock(philo->meta->global_mtx); // signal watcher that you want to perform an action
		print_action(TAKING_FORK, philo); // this also can take time
		pthread_mutex_unlock(philo->meta->global_mtx); // signal watcher that you finished an action and he should check deaths
	}

	// printf("philo %i wants to do an action\n", philo->id);
	// pthread_mutex_lock(philo->meta->global_mtx); // signal watcher that you want to perform an action
	pthread_mutex_lock(philo->right_fork->mutex); // get in queue to get a fork
	pthread_mutex_lock(philo->meta->global_mtx); // signal watcher that you want to perform an action
	print_action(TAKING_FORK, philo); // this also can take time
	pthread_mutex_unlock(philo->meta->global_mtx); // signal watcher that you finished an action and he should check deaths

	if (philo->id % 2 != 0)
	{
		// printf("philo %i wants to do an action\n", philo->id);
		// pthread_mutex_lock(philo->meta->global_mtx); // signal watcher that you want to perform an action
		pthread_mutex_lock(philo->left_fork->mutex); // get in queue to get a fork
		pthread_mutex_lock(philo->meta->global_mtx); // signal watcher that you want to perform an action
		print_action(TAKING_FORK, philo);
		pthread_mutex_unlock(philo->meta->global_mtx); // signal watcher that you finished an action and he should check deaths
	}
}

void	eat(t_philosopher *philo)
{
	philo->last_meal_ms = time_in_ms();

	pthread_mutex_lock(philo->meta->global_mtx); // signal watcher that you want to perform an action
	print_action(EATING, philo);
	pthread_mutex_unlock(philo->meta->global_mtx); // signal watcher that you finished an action and he should check deaths
	sleep_ms(philo->meta->time_to_eat);
	philo->times_eaten += 1;
}

void	put_down_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->left_fork->mutex);
	pthread_mutex_unlock(philo->right_fork->mutex);
}

void	philo_sleep(t_philosopher *philo)
{

	pthread_mutex_lock(philo->meta->global_mtx); // signal watcher that you want to perform an action
	print_action(SLEEPING, philo);
	pthread_mutex_unlock(philo->meta->global_mtx); // signal watcher that you finished an action and he should check deaths
	sleep_ms(philo->meta->time_to_sleep);
}
