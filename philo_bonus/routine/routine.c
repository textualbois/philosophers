/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 23:28:33 by ivansemin         #+#    #+#             */
/*   Updated: 2024/07/19 18:13:06 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*philosopher_routine(t_philosopher *philo);
static void	*watcher_routine(void *arg);

static void	*start_philo(t_parameters *params, int id)
{
	t_philosopher *philo;

	philo = params->philo;
	// printf("here\n");
	if (init_philo_id(id, &philo) != 0)
		exit(1);
	// printf("philo id is %i\n", philo->id);
	if (pthread_create(philo->meta->watcher, NULL, watcher_routine, (void *)philo) != 0)
		exit(1);
	philosopher_routine(philo);
	exit(0);
}

static void	*philosopher_routine(t_philosopher *philo)
{
	while (true)
	{
		if (think(philo) != 0)
			break ;
		if (pick_up_forks(philo) != 0)
			break ;
		if (eat(philo) != 0)
			break ;
		put_down_forks(philo);
		// if (philo_full(philo) == true)
		// 	break ;
		if (philo_sleep(philo) != 0)
			break ;
	}
	// printf("woooo\n");
	sem_close(philo->sem);
	return (NULL);
}

static void	*watcher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *) arg;
	// while (any_deaths(philo->meta->death_watcher) == false)
	while (1)
	{
		if (has_starved(philo))
		{
			register_death(philo);
				break;
		}
		usleep(1000);
	}
	return (NULL);
}

int	run_routines(t_parameters *params)
{
	pid_t	pid;
	int		philo_id;

	if (slim_calloc((void**)&(params->kids), sizeof(pid_t) * params->philosopher_count) != 0)
		return (1);
	printf("kids allocated\n");
	if (pthread_create(params->bouncer, NULL, bouncer_routine, (void *)params) != 0)
		exit(1);
	printf("bouncer thread ready\n");
	philo_id = 1;
	params->start_time = time_in_ms();
	while (philo_id <= params->philosopher_count)
	{
		pid = fork();
		if (pid == CHILD)
			start_philo(params, philo_id);
		else if (pid == -1)
			return (kill_kids(&params->kids, philo_id - 2));
		else
			params->kids[philo_id - 1] = pid;
		philo_id++;
	}
	//free(params->kids);
	pid = waitpid(0, NULL, 0);
	while (pid != -1)
		pid = waitpid(0, NULL, 0);
	//free(params->kids);
	return (0);
}
