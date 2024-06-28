/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivansemin <ivansemin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:45:26 by isemin            #+#    #+#             */
/*   Updated: 2024/06/28 18:43:26 by ivansemin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_params(t_philosopher *head)
{
	free(head->meta->watcher);
	pthread_mutex_destroy(head->meta->global_mtx);
	free(head->meta->global_mtx);
	free(head->meta);
}

t_philosopher	*clean_philo_return_previous(t_philosopher *philo)
{
	t_philosopher *prev;

	prev = philo->last;
	free(philo->thread);
	philo->thread = NULL;
	free(philo);
	return (prev);
}

t_philosopher	*clean_philo_return_next(t_philosopher *philo)
{
	t_philosopher *next;

	next = philo->next;
	free(philo->thread);
	philo->thread = NULL;
	free(philo);
	return (next);
}

void	*full_clean(t_philosopher *head)
{
	t_philosopher *temp;

	temp = head->next;
	if (temp == NULL)
		temp = head;
	clean_params(head);
	while (temp != head)
	{
		pthread_mutex_lock(temp->right_fork->mutex);
		pthread_mutex_unlock(temp->right_fork->mutex);
		pthread_mutex_destroy(temp->right_fork->mutex);
		free(temp->right_fork->mutex);
		free(temp->right_fork);
		temp = clean_philo_return_next(temp);
	}
	pthread_mutex_lock(temp->right_fork->mutex);
	pthread_mutex_unlock(temp->right_fork->mutex);
	pthread_mutex_destroy(temp->right_fork->mutex);
	free(temp->right_fork->mutex);
	free(temp->right_fork);
	clean_philo_return_next(temp);
	return (NULL);
}
