/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:23:32 by isemin            #+#    #+#             */
/*   Updated: 2024/07/03 07:37:25 by isemin           ###   ########.fr       */
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
	philo_dead(philo); //lets the current philo print
	sem_open("/death", O_CREAT, 0644, 0); //blocks further prints
	//perhaps sem_post the philo sem here
	return (NULL);
}

int	any_deaths(void) //done
{
	sem_t	*death;

	death = sem_open("/death", 0);
	if (death == SEM_FAILED)
		return (false);
	sem_close(death);
	return (true);
}
