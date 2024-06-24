/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 01:55:21 by ivansemin         #+#    #+#             */
/*   Updated: 2024/06/24 22:34:09 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philosopher *philo)
{
	print_action(THINKING, philo);
}

void	pick_up_forks(t_philosopher *philo)
{
	if (has_starved(philo))
		philo_dead(philo);

	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork->mutex); // this can take time
		if (has_starved(philo))	// so check again if philo starved
			philo_dead(philo);
		print_action(TAKING_FORK, philo); // this also can take time
	}

	if (has_starved(philo))	// so check again if philo starved
		philo_dead(philo);

	pthread_mutex_lock(philo->right_fork->mutex); // this can also take time
	if (has_starved(philo)) // so check again if starved
		philo_dead(philo);
	print_action(TAKING_FORK, philo); // this also can take time

	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->left_fork->mutex); // this can take time
		if (has_starved(philo))	// so check again if philo starved
			philo_dead(philo);
		print_action(TAKING_FORK, philo);
	}
}

void	eat(t_philosopher *philo)
{
	philo->last_meal_ms = time_in_ms();
	print_action(EATING, philo);
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
	print_action(SLEEPING, philo);
	sleep_ms(philo->meta->time_to_sleep);
}
