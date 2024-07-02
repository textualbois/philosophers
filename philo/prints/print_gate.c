/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_gate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:00:26 by isemin            #+#    #+#             */
/*   Updated: 2024/07/02 03:29:02 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(int action, t_philosopher *philo)
{
	static pthread_mutex_t	print_gate = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&print_gate);
	if (philo->meta->light == GREEN)
	{
		if (action == THINKING && get_set_time(\
				CUM_TIMES_EATEN, philo, 0) != philo->meta->ttl_eating_limit)
			print_thinking(philo);
		else if (action == TAKING_FORK)
			print_taking_fork(philo);
		else if (action == EATING)
			print_eating(philo);
		else if (action == SLEEPING && get_set_time(\
				CUM_TIMES_EATEN, philo, 0) != philo->meta->ttl_eating_limit)
			print_sleeping(philo);
	}
	else if (action == DEATH)
	{
		print_death(philo);
	};
	pthread_mutex_unlock(&print_gate);
}
