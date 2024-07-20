/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:45:26 by isemin            #+#    #+#             */
/*   Updated: 2024/07/20 04:14:44 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	kill_kids(pid_t **kids, int start_from, int res)
{
	while (start_from >= 0)
	{
		kill((*kids)[start_from], SIGTERM);
		start_from--;
	}
	free(*kids);
	return (res);
}

int	kill_kids_except(pid_t **kids, int start_from, pid_t pid)
{
	while (start_from >= 0)
	{
		if ((*kids)[start_from] != pid)
			kill((*kids)[start_from], SIGTERM);
		start_from--;
	}
	free(*kids);
	return (0);
}

int	clean_sems(t_parameters *params)
{
	destroy_semaphore(params->forks, "/forks");
	destroy_semaphore(params->death_watcher, "/death_watcher");
	destroy_semaphore(params->printer, "/print");
	destroy_semaphore(params->time, "/time");
	return (0);
}
