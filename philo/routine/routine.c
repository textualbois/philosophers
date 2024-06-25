/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 23:28:33 by ivansemin         #+#    #+#             */
/*   Updated: 2024/06/25 21:09:13 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philosopher_routine(void *arg)
{
	t_philosopher	*phil;

	phil = (t_philosopher *) arg;
	while (1)
	{
		think(phil);
		pick_up_forks(phil);
		eat(phil);
		put_down_forks(phil);
		philo_sleep(phil);
	}
}

static void	*watcher_routine(void *arg)
{
	t_philosopher	*head;
	t_philosopher	*temp;
	int				i;

	head = (t_philosopher *) arg;
	while (1)
	{
		temp = head;
		i = 1;
		pthread_mutex_lock(head->meta->global_mtx);
		while (i <= temp->id && head->meta->light )
		{
			if (has_starved(temp))
			{
				philo_dead(temp);
				head->meta->light = RED;
			}
		}
		pthread_mutex_unlock(head->meta->global_mtx);
	}
}

void	run_routines(t_philosopher *head)
{
	t_philosopher	*temp;

	temp = head;
	if (pthread_create(temp->thread, NULL, philosopher_routine, (void *)temp) != 0)
		return (clean_up(0)); // some cleanup
	temp = temp->right_fork->right_thread;
	while (temp != head)
	{
		if (pthread_create(temp->thread, NULL, philosopher_routine, (void *)temp) != 0)
			return (full_clean(0)); // other clean
		temp = temp->right_fork->right_thread;
	}

	if (pthread_create(temp->thread, NULL, watcher_routine, (void *)temp) != 0)
		return (clean_up(0)); // some cleanup

	pthread_join(*(temp->thread), NULL);
	temp = temp->right_fork->right_thread;
	while (temp != head)
	{
		pthread_join(*(temp->thread), NULL);
		temp = temp->right_fork->right_thread;
	}
}
