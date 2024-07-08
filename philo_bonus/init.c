/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:01:53 by isemin            #+#    #+#             */
/*   Updated: 2024/07/07 18:36:51 by isemin           ###   ########.fr       */
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
		else if (init_main_semaphores(params) != 0)
		{
			free(params);
			free(params->watcher);
			return (NULL);
		}
		params->start_time = time_in_ms();
	}
	return (params);
}

t_philosopher	*init_philosopher(t_parameters *params)
{
	t_philosopher	*philosopher;

	philosopher = NULL;
	if (slim_calloc((void **)&philosopher, sizeof(t_philosopher)) == 0)
	{
		philosopher->status = THINKING;
		philosopher->meta = params;
	}
	return (philosopher);
}


int	init_philo_id(int count, t_philosopher **philosopher)
{
	char			*sem_name;

	sem_name = create_sem_name(count);
	if (sem_name == NULL)
	{
		return (-1);
	}
	if (init_semaphore(&(*philosopher)->sem, sem_name, 1) != 0)
	{
		free(sem_name);
		return (-1);
	}
	(*philosopher)->id = count;
	(*philosopher)->order = count % 2;
	(*philosopher)->last_meal_ms = (*philosopher)->meta->start_time;
	free(sem_name);
	return (0);
}

int	init_main_semaphores(t_parameters *params)
{
	if (init_semaphore(&(params->forks), "/forks", params->philosopher_count) != 0)
		return (1);
	else if (init_semaphore(&(params->death_watcher), "/death_watcher", 1) != 0)
	{
		destroy_semaphore(params->forks, "/forks");
		return (1);
	}
	else if (init_semaphore(&(params->printer), "/print", 1) != 0)
	{
		destroy_semaphore(params->forks, "/forks");
		destroy_semaphore(params->death_watcher, "/death_watcher");
		return (1);
	}
	else if (init_semaphore(&(params->time), "/time", 1) != 0)
	{
		destroy_semaphore(params->forks, "/forks");
		destroy_semaphore(params->death_watcher, "/death_watcher");
		destroy_semaphore(params->death_watcher, "/death_watcher");
		return (1);
	}
	return (0);
}
