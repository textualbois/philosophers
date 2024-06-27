/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 23:28:33 by ivansemin         #+#    #+#             */
/*   Updated: 2024/06/27 21:40:38 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philosopher_routine(void *arg)
{
	t_philosopher	*phil;

	phil = (t_philosopher *) arg;
	pthread_mutex_lock(phil->meta->global_mtx);
	pthread_mutex_unlock(phil->meta->global_mtx);
	if (phil->id % 2 == 0)
		usleep(5);
	while (phil->meta->light == GREEN)
	{
		think(phil);
		pick_up_forks(phil);
		eat(phil);
		put_down_forks(phil);
		philo_sleep(phil);
	}
	return (NULL);
}

static void	*watcher_routine(void *arg)
{
	t_philosopher	*head;
	t_philosopher	*temp;
	int				i;

	head = (t_philosopher *) arg;
	pthread_mutex_lock(head->meta->global_mtx);
	pthread_mutex_unlock(head->meta->global_mtx);
	while(head->meta->light == GREEN)
	{
		temp = head;
		i = 1;
		pthread_mutex_unlock(head->meta->global_mtx);
		pthread_mutex_lock(head->meta->global_mtx);
		while (i <= temp->id && head->meta->light == GREEN)
		{
			if (has_starved(temp))
			{
				head->meta->light = RED;
				philo_dead(temp);
			}
			temp = temp->next;
			i++;
		}
	}
	return (NULL);
}

static void	waith_for_threads(t_philosopher *head)
{
	t_philosopher	*temp;

	temp = head;
	pthread_join(*(head->meta->watcher), NULL);
	pthread_join(*(temp->thread), NULL);
	temp = temp->next;
	while (temp != head)
	{
		pthread_join(*(temp->thread), NULL);
		temp = temp->next;
	}
}

void	*run_routines(t_philosopher *head)
{
	t_philosopher	*temp;

	temp = head;
	if (pthread_create(temp->thread, NULL, philosopher_routine, (void *)temp) != 0)
		return (NULL);
	temp = temp->next;
	pthread_mutex_lock(head->meta->global_mtx);
	while (temp != head)
	{
		if (pthread_create(temp->thread, NULL, philosopher_routine, (void *)temp) != 0)
			return (NULL);
		temp = temp->next;
	}
	if (pthread_create(head->meta->watcher, NULL, watcher_routine, (void *)head) != 0)
		return (NULL);
	head->meta->start_time = time_in_ms();
	pthread_mutex_unlock(head->meta->global_mtx);
	waith_for_threads(head);
	return (NULL);
}
