/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:45:26 by isemin            #+#    #+#             */
/*   Updated: 2024/07/03 09:36:36 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int kill_kids(pid_t **kids, int start_from)
{
	while(start_from >= 0)
	{
		kill((*kids)[start_from], SIGTERM);
		start_from--;
	}
	free(*kids);
	return (1);
}

// t_philosopher	*clean_philo_return_previous(t_philosopher *philo)
// {
// 	t_philosopher *prev;

// 	prev = philo->last;
// 	free(philo->thread);
// 	philo->thread = NULL;
// 	free(philo);
// 	return (prev);
// }

// t_philosopher	*clean_philo_return_next(t_philosopher *philo)
// {
// 	t_philosopher *next;

// 	next = philo->next;
// 	free(philo->thread);
// 	philo->thread = NULL;
// 	free(philo);
// 	return (next);
// }

// void	*full_clean(t_philosopher *head)
// {
// 	t_philosopher *temp;

// 	temp = head->next;
// 	if (temp == NULL)
// 		temp = head;
// 	clean_params(head);
// 	while (temp != head)
// 	{
// 		pthread_mutex_lock(temp->right_fork->mutex);
// 		pthread_mutex_unlock(temp->right_fork->mutex);
// 		pthread_mutex_destroy(temp->right_fork->mutex);
// 		free(temp->right_fork->mutex);
// 		free(temp->right_fork);
// 		temp = clean_philo_return_next(temp);
// 	}
// 	pthread_mutex_lock(temp->right_fork->mutex);
// 	pthread_mutex_unlock(temp->right_fork->mutex);
// 	pthread_mutex_destroy(temp->right_fork->mutex);
// 	free(temp->right_fork->mutex);
// 	free(temp->right_fork);
// 	clean_philo_return_next(temp);
// 	return (NULL);
// }

int clean_sems(t_parameters *params)
{
	destroy_semaphore(params->forks, "/forks");
	destroy_semaphore(params->death_watcher, "/global");
	destroy_semaphore(params->printer, "/print");
	destroy_semaphore(params->time, "/time");
	return (0);
}
