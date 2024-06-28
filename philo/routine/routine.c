/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivansemin <ivansemin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 23:28:33 by ivansemin         #+#    #+#             */
/*   Updated: 2024/06/28 20:22:17 by ivansemin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philosopher_routine(void *arg)
{
	t_philosopher	*phil;

	phil = (t_philosopher *) arg;

	//printf("philo %i takes global lock\n", phil->id);
	//printf("philo %i global lock is %p\n", phil->id, phil->meta->global_mtx);
	pthread_mutex_lock(phil->meta->global_mtx);
	pthread_mutex_unlock(phil->meta->global_mtx);
	//printf("philo %i releases global lock\n", phil->id);
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
	//printf("watcher takes global lock\n");

	//printf("watcher global lock is %p\n", head->meta->global_mtx);
	pthread_mutex_lock(head->meta->global_mtx);
	// usleep(1000);
	// head->meta->start_time = time_in_ms();
	//printf("watcher releases global lock\n");
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
				pthread_mutex_unlock(head->meta->global_mtx);
				return (NULL);
			}
			temp = temp->next;
			i++;
		}
	}
	pthread_mutex_unlock(head->meta->global_mtx);
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

	pthread_mutex_lock(head->meta->global_mtx);
	if (pthread_create(head->meta->watcher, NULL, watcher_routine, (void *)head) != 0)
		return (full_clean(head));
	if (pthread_create(temp->thread, NULL, philosopher_routine, (void *)temp) != 0)
		return (full_clean(head));
	temp = temp->next;
	while (temp != head)
	{
		if (pthread_create(temp->thread, NULL, philosopher_routine, (void *)temp) != 0)
			return (full_clean(head));
		temp = temp->next;
	}
	// if (pthread_create(head->meta->watcher, NULL, watcher_routine, (void *)head) != 0)
	// 	return (NULL);

	head->meta->start_time = time_in_ms();
	
	pthread_mutex_unlock(head->meta->global_mtx);
	waith_for_threads(head);
	return (NULL);
}
