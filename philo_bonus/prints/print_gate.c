/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_gate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:00:26 by isemin            #+#    #+#             */
/*   Updated: 2024/07/20 20:00:42 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	print_action(int action, t_philosopher *philo)
{
	sem_wait(philo->meta->printer);
	if (any_deaths() == false)
	{
		if (action == THINKING)
			print_thinking(philo);
		else if (action == TAKING_FORK)
			print_taking_fork(philo);
		else if (action == EATING)
			print_eating(philo);
		else if (action == SLEEPING)
			print_sleeping(philo);
		sem_post(philo->meta->printer);
		return (0);
	}
	else if (action == DEATH)
	{
		print_death(philo);
	}
	sem_post(philo->meta->printer);
	return (0);
}
