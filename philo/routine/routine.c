/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 23:28:33 by ivansemin         #+#    #+#             */
/*   Updated: 2024/06/27 18:27:32 by isemin           ###   ########.fr       */
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
	//printf("routine for philo %i has started\n", phil->id);
	while (1)
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

	printf("started watcher\n");
	head = (t_philosopher *) arg;
	while(1)
	{
		temp = head;
		i = 1;
		pthread_mutex_lock(head->meta->global_mtx);
		// printf("watcher took mutex\n");
		// printf("i = %i\nphilo = %i\nlight = %s\n", i, temp->id, temp->meta->light == GREEN ? "GREEN" : "RED");
		while (i <= temp->id && head->meta->light == GREEN)
		{
			//printf("checking if philo %i is dead\n", temp->id);
			if (has_starved(temp))
			{
				//printf("philo %i has starved\n##################################################\n", temp->id);
				head->meta->light = RED;
				philo_dead(temp);
				head->meta->light = RED;
			}
			temp = temp->next;
			i++;
		}
		pthread_mutex_unlock(head->meta->global_mtx);
	}
	return (NULL);
}

void	*run_routines(t_philosopher *head)
{
	t_philosopher	*temp;

	temp = head;
	if (pthread_create(temp->thread, NULL, philosopher_routine, (void *)temp) != 0)
		return (NULL);//return (clean_up(0)); // some cleanup
	temp = temp->next;
	// printf("head:       %p\nright philo %p <- through head\nright philo %p <- through temp (shoould be larger)\n left philo %p <- through head\n left philo %p <- through temp - should be same as head philo\n",
	// 		head, head->next, temp->next,
	// 		head->left_fork->left_thread, temp->left_fork->left_thread);
	// printf("head adress %p\ntemp adress %p\n",head, temp);
	pthread_mutex_lock(head->meta->global_mtx);
	while (temp != head)
	{
		// printf("creating thread for philo id %i\n", temp->id);
		if (pthread_create(temp->thread, NULL, philosopher_routine, (void *)temp) != 0)
			return (NULL);//return (full_clean(0)); // other clean
		temp = temp->next;
	}

	if (pthread_create(head->meta->watcher, NULL, watcher_routine, (void *)head) != 0)
		return (NULL);// return (clean_up(0)); // some cleanup

	head->meta->start_time = time_in_ms();
	pthread_mutex_unlock(head->meta->global_mtx);
	pthread_join(*(head->meta->watcher), NULL);
	return (NULL);
	pthread_join(*(temp->thread), NULL);
	temp = temp->next;
	// printf("temp id is %i\n", temp->id);
	while (temp != head)
	{
		// printf("temp id is %i\n", temp->id);
		pthread_join(*(temp->thread), NULL);
		temp = temp->next;
	}

}
