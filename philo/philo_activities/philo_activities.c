/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 01:55:21 by ivansemin         #+#    #+#             */
/*   Updated: 2024/06/23 19:24:33 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	think(t_philosopher *philo)
{
	printf("%i %s is thinking\n", time, philo->name);
}

void	pick_up_forks(t_philosopher *philo)
{
	if (has_starved(philo))
		philo_dead(philo);
	pthread_mutex_lock(philo->left_fork->mutex);
	if (has_starved(philo))
		philo_dead(philo);
	printf("%i %s has taken a fork\n", time, philo->name);
	if (has_starved(philo))
		philo_dead(philo);
	pthread_mutex_lock(philo->right_fork->mutex);
	if (has_starved(philo))
		philo_dead(philo);
	printf("%i %s has taken a fork\n", time, philo->name);
	if (has_starved(philo))
		philo_dead(philo);
	pthread_mutex_lock(philo->right_fork->mutex);


}

void	eat(t_philosopher *philo)
{
	usleep(philo->meta->time_to_eat);
	philo->times_eaten += 1;
}

void	put_down_forks(t_philosopher *philo)
{

}

void	sleep(t_philosopher *philo)
{

}
