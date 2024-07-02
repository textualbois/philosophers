/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:01:53 by isemin            #+#    #+#             */
/*   Updated: 2024/07/02 11:08:24 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @brief malloc parameters
 *
 * @param argc
 * @param argv[1] number_of_philosophers
 * @param argv[2] time_to_die
 * @param argv[3] time_to_eat
 * @param argv[4] time_to_sleep
 * @param argv[5] eating_limit (optional)
 * @return ptr to t_parameters
 */
t_parameters	*init_parameters(int argc, char **argv)
{
	t_parameters	*params;

	params = NULL;
	if (slim_calloc((void**)&params, sizeof(t_parameters)) == 0)
	{
		params->philosopher_count = ft_atoi(argv[1]);
		params->time_to_die = ft_atoi(argv[2]);
		params->time_to_eat = ft_atoi(argv[3]);
		params->time_to_sleep = ft_atoi(argv[4]);
		set_eating_limits(argc, argv, params);
		params->light = RED;
		if (slim_malloc((void**)&(params->watcher), sizeof(pthread_t)) != 0)
		{
			free(params);
			return (NULL);
		}
		else if (init_semaphores(params) != 0)
		{
			free(params);
			free(params->watcher);
			return (NULL);
		}
	}
	return (params);
}

t_philosopher	*init_philosopher(int count, t_parameters *params)
{
	t_philosopher	*philosopher;
	char			*sem_name;

	sem_name = create_sem_name(count);
	if (sem_name == NULL)
		return (NULL);
	philosopher = NULL;
	if (slim_calloc((void **)&philosopher, sizeof(t_philosopher)) == 0)
	{
		if (init_semaphore(&(philosopher->sem), sem_name, 1) != 0)
		{
			free(sem_name);
			free(philosopher);
			return (NULL);
		}
		philosopher->status = THINKING;
		philosopher->id = count;
		philosopher->meta = params;
		philosopher->order = count % 2;
		if (philosopher->meta->philosopher_count == count)
			philosopher->order = LAST_GROUP;
	}
	free(sem_name);
	return (philosopher);
}

int	init_main_semaphores(t_parameters *params)
{
	if (init_semaphore(&(params->forks), "/forks", params->philosopher_count) != 0)
		return (1);
	else if (init_semaphore(&(params->global_sem), "/global", 1) != 0)
	{
		destroy_semaphore(params->forks, "/forks");
		return (1);
	}
	else if (init_semaphore(&(params->printer), "/print", 1) != 0)
	{
		destroy_semaphore(params->forks, "/forks");
		destroy_semaphore(params->global_sem, "/global");
		return (1);
	}
	else if (init_semaphore(&(params->time), "/time", 1) != 0)
	{
		destroy_semaphore(params->forks, "/forks");
		destroy_semaphore(params->global_sem, "/global");
		destroy_semaphore(params->global_sem, "/global");
		return (1);
	}
	return (0);
}

