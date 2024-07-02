/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 23:28:33 by ivansemin         #+#    #+#             */
/*   Updated: 2024/07/02 03:18:35 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philosopher_routine(void *arg)
{
	t_philosopher	*phil;

	phil = (t_philosopher *) arg;
	while (phil->meta->light == RED)
		continue;
	while (phil->meta->light == GREEN && phil->times_eaten != phil->meta->eating_limit)
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
	head->meta->start_time = time_in_ms();
	head->meta->light = GREEN;
	while(head->meta->light == GREEN)
	{
		pthread_mutex_lock(head->meta->global_mtx);
		temp = head;
		i = 0;
		while (++i <= temp->id && head->meta->light == GREEN)
		{
			if (has_starved(temp))
				register_death(temp);
			temp = temp->next;
			//i++;
		}
		if (head->meta->cum_times_eaten == head->meta->ttl_eating_limit)
			head->meta->light = RED;
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
	waith_for_threads(head);
	return (NULL);
}
