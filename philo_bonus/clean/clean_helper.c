/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:18:42 by isemin            #+#    #+#             */
/*   Updated: 2024/07/02 07:34:13 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	destroy_semaphore(sem_t *sem, const char *name)
{
	if (sem_close(sem) == -1)
		exit(EXIT_FAILURE);
	if (sem_unlink(name) == -1)
		exit(EXIT_FAILURE);
}

void	clean_params(t_philosopher *head)
{
	free(head->meta->watcher);
	pthread_mutex_destroy(head->meta->global_mtx);
	free(head->meta->global_mtx);
	free(head->meta);
}