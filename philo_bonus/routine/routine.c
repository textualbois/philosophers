/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 23:28:33 by ivansemin         #+#    #+#             */
/*   Updated: 2024/07/07 13:56:00 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*philosopher_routine(t_philosopher *philo);
static void	*watcher_routine(void *arg);

static void	*start_philo(t_parameters *params, int id)
{
	t_philosopher *philo;

	philo = init_philosopher(id, params);
	if (philo == NULL)
		exit(1);
	if (pthread_create(philo->meta->watcher, NULL, watcher_routine, (void *)philo) != 0)
		exit(1);
	philosopher_routine(philo);
	exit(0);
}

static void	*philosopher_routine(t_philosopher *philo)
{
	while (any_deaths(philo->meta->death_watcher) == false)
	{
		think(philo);
		pick_up_forks(philo);
		eat(philo);
		put_down_forks(philo);
		if (philo_full(philo) == true)
			break ;
		philo_sleep(philo);
	}
	sem_close(philo->sem);
	return (NULL);
}

static void	*watcher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *) arg;
	while (any_deaths(philo->meta->death_watcher) == false)
	{
		if (has_starved(philo))
		{
			register_death(philo);
		}
		usleep(3000);
	}
	return (NULL);
}

int	run_routines(t_parameters *params)
{
	pid_t	pid;
	int		philo_id;
	pid_t	*kids;

	if (slim_calloc((void**)&kids, sizeof(pid_t) * params->philosopher_count) != 0)
		return (1);
	philo_id = 1;
	params->start_time = time_in_ms();
	while (philo_id <= params->philosopher_count)
	{
		pid = fork();
		if (pid == CHILD)
			start_philo(params, philo_id);
		else if (pid == -1)
			return (kill_kids(&kids, philo_id - 2));
		else
			kids[philo_id - 1] = pid;
		philo_id++;
	}
	free(kids);
	pid = waitpid(0, NULL, 0);
	while (pid != -1)
		pid = waitpid(0, NULL, 0);
	return (0);
}
