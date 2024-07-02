/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_gate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:00:26 by isemin            #+#    #+#             */
/*   Updated: 2024/07/02 12:08:05 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_action(int action, t_philosopher *philo)
{

	sem_wait(philo->meta->printer);
	if (any_deaths() == FALSE)
	{
		if (action == THINKING && get_set_time(\
				TIMES_EATEN, philo, 0) != philo->meta->eating_limit)
			print_thinking(philo);
		else if (action == TAKING_FORK)
			print_taking_fork(philo);
		else if (action == EATING)
			print_eating(philo);
		else if (action == SLEEPING && get_set_time(\
				TIMES_EATEN, philo, 0) != philo->meta->eating_limit)
			print_sleeping(philo);
	}
	else if (action == DEATH)
	{
		print_death(philo);
	}
	sem_post(philo->meta->printer);
}
