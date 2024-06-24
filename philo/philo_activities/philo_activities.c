/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivansemin <ivansemin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 01:55:21 by ivansemin         #+#    #+#             */
/*   Updated: 2024/06/24 03:01:49 by ivansemin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	think(t_philosopher *philo)
{
	print_action(THINKING, philo);
}

void	pick_up_forks(t_philosopher *philo)
{
	if (has_starved(philo))
		philo_dead(philo);

	pthread_mutex_lock(philo->left_fork->mutex); // this can take time
	if (has_starved(philo))	// so check again if philo starved
		philo_dead(philo);

	print_action(TAKING_FORK, philo); // this also can take time
	if (has_starved(philo))	// so check again if philo starved
		philo_dead(philo);

	pthread_mutex_lock(philo->right_fork->mutex); // this can also take time
	if (has_starved(philo)) // so check again if starved
		philo_dead(philo);

	print_action(TAKING_FORK, philo); // this also can take time
	// but it doesnt matter, becausae the is going to eat

}

void	eat(t_philosopher *philo)
{
	usleep(philo->meta->time_to_eat);
	philo->times_eaten += 1;
}

void	put_down_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->left_fork->mutex);
	pthread_mutex_unlock(philo->right_fork->mutex);
}

void	sleep(t_philosopher *philo)
{
	print_action(SLEEPING, philo);
	usleep(philo->meta->time_to_sleep);
}
