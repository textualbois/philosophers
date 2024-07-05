/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 23:28:33 by ivansemin         #+#    #+#             */
/*   Updated: 2024/07/05 13:39:28 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philosopher_routine(void *arg)
{
	t_philosopher	*phil;

	phil = (t_philosopher *) arg;
	while (allowed_to_continue(GET, 0) == STOP)
		continue;
	while (allowed_to_continue(GET, 0) == GO)
	{
		// printf("last meal for phil %i was at %i\n", phil->id, phil->last_meal_ms - phil->meta->start_time);
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
	head->meta->start_time = time_in_ms();
	allowed_to_continue(SET, GO);
	while (1)
	{
		temp = head;
		i = 0;
		while (++i <= temp->id)
		{
			if (has_starved(temp))
				return (register_death(temp));
			temp = temp->next;
		}
		if (get_set_time(CUM_TIMES_EATEN, head, 0) == head->meta->ttl_eating_limit) // data_race
			return (allowed_to_continue(SET, STOP), NULL);
		usleep(100);
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
	allowed_to_continue(SET, STOP);
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
	pthread_mutex_unlock(head->meta->global_mtx);
	printf("mutex unlocked\n");
	fflush(stdout);

	waith_for_threads(head);
	return (NULL);
}
