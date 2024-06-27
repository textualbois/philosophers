/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_gate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivansemin <ivansemin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:00:26 by isemin            #+#    #+#             */
/*   Updated: 2024/06/26 17:22:48 by ivansemin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(int action, t_philosopher *philo)
{
	static pthread_mutex_t	print_gate = PTHREAD_MUTEX_INITIALIZER;

	//printf("philo %i has print lock\n", philo->id);
	pthread_mutex_lock(&print_gate);
	if (philo->meta->light == GREEN)
	{
		//	printf("for philo %i the light is %s\n", philo->id, philo->meta->light == RED ? "RED" : "GREEN");
		if (action == THINKING)
			print_thinking(philo);
		else if (action == TAKING_FORK)
			print_taking_fork(philo);
		else if (action == EATING)
			print_eating(philo);
		else if (action == SLEEPING)
			print_sleeping(philo);
	}
	else if (action == DEATH)
	{
		print_death(philo);
	}
	//else
		//print_death(philo);

	pthread_mutex_unlock(&print_gate);
	//printf("philo %i released print lock\n", philo->id);
}
