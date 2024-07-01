/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 01:55:21 by ivansemin         #+#    #+#             */
/*   Updated: 2024/07/01 12:07:18 by isemin           ###   ########.fr       */
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
	pick_up_from_left(philo);
}

void	eat(t_philosopher *philo)
{
	philo->last_meal_ms = time_in_ms();
	print_action(EATING, philo);
	get_set_time(SET, philo, 1);
	sleep_ms(philo->meta->time_to_eat);
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
