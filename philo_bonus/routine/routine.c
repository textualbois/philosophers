/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 23:28:33 by ivansemin         #+#    #+#             */
/*   Updated: 2024/07/02 12:08:07 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*philosopher_routine(t_philosopher *philo);

static void	*start_philo(t_parameters *params, int id)
{
	t_philosopher *philo;

	philo = init_philosopher(id, params);
	if (philo == NULL)
	{
		//handle maybe
		exit(1);
	}
	philosopher_routine(philo);
	exit(0);
}

static void	*philosopher_routine(t_philosopher *philo)
{
	t_philosopher	*phil;

	while (any_deaths() == FALSE)
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
	t_philosopher	*philo;
	int				i;

	philo = (t_philosopher *) arg;
	while (any_deaths() == FALSE)
	{
		sem_wait(philo->sem);
		if (has_starved(philo))
		{
			register_death(philo);
		}
		else if (has_starved(philo))
		{
			register_death
		}
			temp = temp->next;
			//i++;
		}
		if (head->meta->cum_times_eaten == head->meta->ttl_eating_limit)
			head->meta->light = RED;
		pthread_mutex_unlock(head->meta->global_mtx);
	}
	return (NULL);
}

int	run_routines(t_parameters *params)
{
	pid_t	pid;
	int		philo_id;
	pid_t	*kids;

	if (slim_calloc(&kids, sizeof(pid_t) * params->philosopher_count) != 0)
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
