/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:23:32 by isemin            #+#    #+#             */
/*   Updated: 2024/07/02 11:17:19 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	has_starved(t_philosopher *philo)
{
	if (philo->last_meal_ms == 0)
		philo->last_meal_ms = philo->meta->start_time;
	return (time_without_food(philo) > philo->meta->time_to_die);
}

int	philo_dead(t_philosopher *philo)
{
	print_action(DEATH, philo);
	return (0);
}

void	*register_death(t_philosopher *philo)
{
	sem_open("/death", O_CREAT, 0644, 0);
	philo_dead(philo);
	//perhaps sem_post the philo sem here
	return (NULL);
}

int	any_deaths(void)
{
	sem_t	*death;

	death = sem_open("/death", 0);
	if (death == SEM_FAILED)
		return (FALSE);
	sem_close(death);
	return (TRUE)
}

int report_death()