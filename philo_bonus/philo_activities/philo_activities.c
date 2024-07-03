/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 01:55:21 by ivansemin         #+#    #+#             */
/*   Updated: 2024/07/03 10:10:13 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	think(t_philosopher *philo) // protected by any death in watcher and at beginning of routine loop
{
	print_action(THINKING, philo);
	if (philo->order == EVEN_GROUP && philo->times_eaten == 0)
	{
		sleep_ms(philo->meta->time_to_eat / 2);
	}
}

void	pick_up_forks(t_philosopher *philo) //probably done
{
	sem_wait(philo->meta->forks);
//	sem_wait(philo->meta->death_watcher);
	print_action(TAKING_FORK, philo);
//	sem_post(philo->meta->death_watcher);

	sem_wait(philo->meta->forks);
	sem_wait(philo->meta->death_watcher);
	print_action(TAKING_FORK, philo);
	//sem_post(philo->meta->death_watcher);
}

void	eat(t_philosopher *philo) //probably done
{
//	pthread_mutex_lock(philo->meta->global_mtx);
	philo->last_meal_ms = time_in_ms();
	print_action(EATING, philo);
	sem_post(philo->meta->death_watcher);
	get_set_time(SET, philo, 1);
	sleep_ms(philo->meta->time_to_eat);
//	pthread_mutex_unlock(philo->meta->global_mtx);
}

void	put_down_forks(t_philosopher *philo) //done
{
	sem_post(philo->meta->forks);
	sem_post(philo->meta->forks);
}

void	philo_sleep(t_philosopher *philo) //probably_done
{
	print_action(SLEEPING, philo);
	sleep_ms(philo->meta->time_to_sleep);
}
