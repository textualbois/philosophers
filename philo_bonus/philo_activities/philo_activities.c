/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 01:55:21 by ivansemin         #+#    #+#             */
/*   Updated: 2024/07/07 13:54:06 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	think(t_philosopher *philo)
{
	print_action(THINKING, philo);
	if (philo->order == EVEN_GROUP && philo->times_eaten == 0)
		sleep_ms(philo->meta->time_to_eat / 2);
}

void	pick_up_forks(t_philosopher *philo)
{
	sem_wait(philo->meta->forks);
	print_action(TAKING_FORK, philo);
	sem_wait(philo->meta->forks);
	sem_wait(philo->sem);
	print_action(TAKING_FORK, philo);
}

void	eat(t_philosopher *philo)
{
	philo->last_meal_ms = time_in_ms();
	print_action(EATING, philo);
	sem_post(philo->sem);
	get_set_time(SET, philo, 1);
	sleep_ms(philo->meta->time_to_eat);
}

void	put_down_forks(t_philosopher *philo)
{
	sem_post(philo->meta->forks);
	sem_post(philo->meta->forks);
}

void	philo_sleep(t_philosopher *philo)
{
	print_action(SLEEPING, philo);
	sleep_ms(philo->meta->time_to_sleep);
}
