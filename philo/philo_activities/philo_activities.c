/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 01:55:21 by ivansemin         #+#    #+#             */
/*   Updated: 2024/07/05 13:48:31 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philosopher *philo)
{
	print_action(THINKING, philo);
}

void	pick_up_forks(t_philosopher *philo)
{
	while (get_order(philo) != philo->order)
	{
		usleep(300);
	}
	if (philo->order == ODD_GROUP)
		pick_up_from_left(philo);
	else
		pick_up_from_right(philo);
}

void	eat(t_philosopher *philo)
{
//	pthread_mutex_lock(philo->meta->global_mtx);
	get_set_time(SET, philo, 1);
	print_action(EATING, philo);
	sleep_ms(philo->meta->time_to_eat);
//	pthread_mutex_unlock(philo->meta->global_mtx);
}

void	put_down_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->left_fork->mutex);
	pthread_mutex_unlock(philo->right_fork->mutex);
}

void	philo_sleep(t_philosopher *philo)
{

	//pthread_mutex_lock(philo->meta->global_mtx);
	print_action(SLEEPING, philo);
	//pthread_mutex_unlock(philo->meta->global_mtx);
	sleep_ms(philo->meta->time_to_sleep);
}
