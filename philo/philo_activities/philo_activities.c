/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 01:55:21 by ivansemin         #+#    #+#             */
/*   Updated: 2024/07/01 01:16:22 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philosopher *philo)
{
	print_action(THINKING, philo);
}

void	pick_up_forks(t_philosopher *philo)
{
	if (philo->order == ODD_NUMBER)
	{
		pthread_mutex_lock(philo->left_fork->mutex);
		pthread_mutex_lock(philo->meta->global_mtx);
		print_action(TAKING_FORK, philo);
		pthread_mutex_unlock(philo->meta->global_mtx);
	}
	else if (philo->times_eaten == 0)
	{
		sleep_ms(philo->meta->time_to_eat / 2);
	}

	pthread_mutex_lock(philo->right_fork->mutex);
	pthread_mutex_lock(philo->meta->global_mtx);
	print_action(TAKING_FORK, philo);
	pthread_mutex_unlock(philo->meta->global_mtx);

	if (philo->order != ODD_NUMBER)
	{
		pthread_mutex_lock(philo->left_fork->mutex);
		pthread_mutex_lock(philo->meta->global_mtx);
		print_action(TAKING_FORK, philo);
		pthread_mutex_unlock(philo->meta->global_mtx);
	}
}

void	eat(t_philosopher *philo)
{
	philo->last_meal_ms = time_in_ms();

	pthread_mutex_lock(philo->meta->global_mtx);
	print_action(EATING, philo);
	pthread_mutex_unlock(philo->meta->global_mtx);
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

	pthread_mutex_lock(philo->meta->global_mtx);
	print_action(SLEEPING, philo);
	pthread_mutex_unlock(philo->meta->global_mtx);
	sleep_ms(philo->meta->time_to_sleep);
}
