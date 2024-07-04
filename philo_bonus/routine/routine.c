/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 23:28:33 by ivansemin         #+#    #+#             */
/*   Updated: 2024/07/04 10:03:03 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*philosopher_routine(t_philosopher *philo);
static void	*watcher_routine(void *arg);


static void	*start_philo(t_parameters *params, int id)
{
	t_philosopher *philo;

	philo = init_philosopher(id, params); //done
	if (philo == NULL)
	{
		//handle maybe
		exit(1);
	}
	if (pthread_create(philo->meta->watcher, NULL, watcher_routine, (void *)philo) != 0)
		exit(1);
	philosopher_routine(philo); //to do
	exit(0);
}

static void	*philosopher_routine(t_philosopher *philo) //DOING NOW
{
	while (any_deaths(philo->meta->death_watcher) == false) //done
	{
		think(philo); //todo
		pick_up_forks(philo); //todo
		eat(philo); //todo
		put_down_forks(philo); //todo
		if (philo_full(philo) == true) //done
			break ;
		philo_sleep(philo); //todo
	}
	sem_close(philo->sem);
	return (NULL);
}

static void	*watcher_routine(void *arg) // maybe done
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

int	run_routines(t_parameters *params) // done
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
			start_philo(params, philo_id); // check error handling
		else if (pid == -1)
			return (kill_kids(&kids, philo_id - 2)); //done
		else
			kids[philo_id - 1] = pid;
		philo_id++;
	}
	free(kids); //done
	pid = waitpid(0, NULL, 0);
	while (pid != -1)
		pid = waitpid(0, NULL, 0);
	return (0);
}
