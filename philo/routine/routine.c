/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivansemin <ivansemin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 23:28:33 by ivansemin         #+#    #+#             */
/*   Updated: 2024/06/24 03:11:09 by ivansemin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	*philosopher_routine(void *arg)
{
	t_philosopher *phil;

	phil = (t_philosopher *) arg;
	while (1)
	{
		think(phil);
		pick_up_forks(phil);
		eat(phil);
		put_down_forks(phil);
		sleep(phil);
	}
}

void	run_routines(t_philosopher *head)
{
	t_philosopher	*temp;

	temp = head;
	pthread_create(temp->thread, NULL, philosopher_routine, (void *)temp);
	temp = temp->right_fork->right_thread;
	while (temp != head)
	{
		pthread_create(temp->thread, NULL, philosopher_routine, (void *)temp);
		temp = temp->right_fork->right_thread;
	}

	pthread_join(*(temp->thread), NULL);
	temp = temp->right_fork->right_thread;
	while (temp != head)
	{
		pthread_join(*(temp->thread), NULL);
		temp = temp->right_fork->right_thread;
	}
}
