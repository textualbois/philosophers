/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 23:28:33 by ivansemin         #+#    #+#             */
/*   Updated: 2024/07/01 06:30:20 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philosopher_routine(void *arg)
{
	t_philosopher	*phil;

	phil = (t_philosopher *) arg;
	while (phil->meta->light == RED)
		continue;
	if (phil->id % 2 == 0)
		usleep(5);
	while (phil->meta->light == GREEN && phil->times_eaten != phil->meta->eating_limit)
	{

		// printf("philo loop\n");
		// fflush(stdout);
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
	// printf("watcher\n");
	// fflush(stdout);

	head = (t_philosopher *) arg;
	head->meta->start_time = time_in_ms();
	head->meta->light = GREEN;
	while(head->meta->light == GREEN)
	{
	//printf("watcher_loop\n");
	//fflush(stdout);

		pthread_mutex_lock(head->meta->global_mtx);
		temp = head;
		i = 1;
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
		if (head->meta->cum_times_eaten == head->meta->ttl_eating_limit)
		{
			head->meta->light = RED;
		}
		pthread_mutex_unlock(head->meta->global_mtx);
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

	//pthread_mutex_lock(head->meta->global_mtx);
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

	//pthread_mutex_unlock(head->meta->global_mtx);
	waith_for_threads(head);
	return (NULL);
}
