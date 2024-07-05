/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_gate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:00:26 by isemin            #+#    #+#             */
/*   Updated: 2024/07/05 11:28:45 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(int action, t_philosopher *philo)
{
	static pthread_mutex_t	print_gate = PTHREAD_MUTEX_INITIALIZER;
	int						go_on;

	go_on = allowed_to_continue(GET, 0);
	if (go_on == GO)
	{
		if (action == THINKING)
			print_thinking(philo, &print_gate);
		else if (action == TAKING_FORK)
			print_taking_fork(philo, &print_gate);
		else if (action == EATING)
			print_eating(philo, &print_gate);
		else if (action == SLEEPING)
			print_sleeping(philo, &print_gate);
	}
	else if (action == DEATH && go_on == philo->id)
	{
		print_death(philo, &print_gate);
	}
}
