/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:23:32 by isemin            #+#    #+#             */
/*   Updated: 2024/07/04 10:13:09 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	has_starved(t_philosopher *philo) //done
{
	return (time_without_food(philo) > philo->meta->time_to_die);
}

int	philo_dead(t_philosopher *philo) //probably done
{
	print_action(DEATH, philo);
	return (0);
}

void	*register_death(t_philosopher *philo) //probably done
{
	sem_wait(philo->meta->death_watcher);
	philo_dead(philo); //lets the current philo print
	sem_open("/death", O_CREAT, 0644, 0); //blocks further prints
	sem_post(philo->meta->death_watcher);
	//perhaps sem_post the philo sem here
	return (NULL);
}

int	any_deaths(sem_t *lock) //done
{
	sem_t	*death;

	sem_wait(lock);
	death = sem_open("/death", 0);
	if (death == SEM_FAILED)
	{
		sem_post(lock);
		return (false);
	}
	printf("DEATH AQUIRED\n");
	fflush(stdout);
	sem_close(death);
	sem_post(lock);
	return (true);
}
