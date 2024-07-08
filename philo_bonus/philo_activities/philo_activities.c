/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 01:55:21 by ivansemin         #+#    #+#             */
/*   Updated: 2024/07/07 17:55:22 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	think(t_philosopher *philo)
{
	if (print_action(THINKING, philo) != 0)
		return (-1);
	if (philo->order == EVEN_GROUP && philo->times_eaten == 0)
		sleep_ms(philo->meta->time_to_eat / 2);
	return (0);
}

int	pick_up_forks(t_philosopher *philo)
{
	sem_wait(philo->meta->forks);
	if (print_action(TAKING_FORK, philo) != 0)
	{
		sem_post(philo->meta->forks);
		return (-1);
	}
	sem_wait(philo->meta->forks);
	sem_wait(philo->sem);
	if (print_action(TAKING_FORK, philo) != 0)
	{
		put_down_forks(philo);
		return (-1);
	}
	return (0);
}

int	eat(t_philosopher *philo)
{
	philo->last_meal_ms = time_in_ms();
	if (print_action(EATING, philo) != 0)
	{
		sem_post(philo->sem);
		return (-1);
	}
	sem_post(philo->sem);
	get_set_time(SET, philo, 1);
	sleep_ms(philo->meta->time_to_eat);
	return (0);
}

void	put_down_forks(t_philosopher *philo)
{
	sem_post(philo->meta->forks);
	sem_post(philo->meta->forks);
}

int	philo_sleep(t_philosopher *philo)
{
	if (print_action(SLEEPING, philo) != 0)
	{
		return (-1);
	}
	sleep_ms(philo->meta->time_to_sleep);
	return (0);
}
