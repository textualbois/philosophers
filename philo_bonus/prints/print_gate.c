/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_gate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:00:26 by isemin            #+#    #+#             */
/*   Updated: 2024/07/04 10:01:23 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_action(int action, t_philosopher *philo)
{
	sem_wait(philo->meta->printer);
	if (any_deaths(philo->meta->death_watcher) == false)
	{
		if (action == THINKING)
			print_thinking(philo);
		else if (action == TAKING_FORK)
			print_taking_fork(philo);
		else if (action == EATING)
			print_eating(philo);
		else if (action == SLEEPING)
			print_sleeping(philo);
		else if (action == DEATH)
		{
			print_death(philo);
			usleep(200); //maybe don't need it
		}
	}
	sem_post(philo->meta->printer);
}
