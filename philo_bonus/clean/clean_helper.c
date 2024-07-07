/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:18:42 by isemin            #+#    #+#             */
/*   Updated: 2024/07/07 17:15:52 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	destroy_semaphore(sem_t *sem, const char *name)
{
	if (sem_close(sem) == -1)
	{
		printf("failed to close for %s\n", name);
		exit(EXIT_FAILURE);
	}
	if (sem_unlink(name) == -1)
		exit(EXIT_FAILURE);
}

void	clean_params(t_parameters **params)
{
	sem_t	*death;

	free((*params)->watcher);
	destroy_semaphore((*params)->time, "/time");
	destroy_semaphore((*params)->death_watcher, "/death_watcher");
	destroy_semaphore((*params)->printer, "/print");
	destroy_semaphore((*params)->forks, "/forks");
	death = sem_open("/death", 0);
	if (death != SEM_FAILED)
	{
		sen_close(death);
		sem_unlink("/death");
	}
	free(*params);
}
