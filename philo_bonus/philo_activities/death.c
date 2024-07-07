/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:23:32 by isemin            #+#    #+#             */
/*   Updated: 2024/07/07 13:56:33 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	has_starved(t_philosopher *philo)
{
	return (time_without_food(philo) > philo->meta->time_to_die);
}

int	philo_dead(t_philosopher *philo)
{
	print_action(DEATH, philo);
	return (0);
}

void	*register_death(t_philosopher *philo)
{
	sem_wait(philo->meta->death_watcher);
	philo_dead(philo);
	sem_open("/death", O_CREAT, 0644, 0);
	sem_post(philo->meta->death_watcher);
	return (NULL);
}

int	any_deaths(sem_t *lock)
{
	sem_t	*death;

	sem_wait(lock);
	death = sem_open("/death", 0);
	if (death == SEM_FAILED)
	{
		sem_post(lock);
		return (false);
	}
	sem_close(death);
	sem_post(lock);
	return (true);
}
