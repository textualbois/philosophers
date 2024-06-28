/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivansemin <ivansemin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:01:53 by isemin            #+#    #+#             */
/*   Updated: 2024/06/28 18:04:54 by ivansemin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		params->eating_limit = set_eating_limit(argc, argv);
		params->light = GREEN;
		if (slim_malloc((void**)&(params->watcher), sizeof(pthread_t)) != 0)
		{
			free(params);
			return (NULL);
		}
		else if (init_mutex(&(params->global_mtx)) != 0)
		{
			free(params);
			free(params->watcher);
			return (NULL);
		}
		params->start_time = time_in_ms();
	}
	return (params);
}

t_philosopher	*init_philosopher(int count, t_parameters *params)
{
	t_philosopher	*philosopher;

	philosopher = malloc(sizeof(t_philosopher));
	if (philosopher != NULL)
	{
		if (slim_calloc((void **)&(philosopher->thread), sizeof(pthread_t)) != 0)
		{
			free(philosopher);
			return (NULL);
		}
		philosopher->left_fork = NULL;
		philosopher->right_fork = NULL;
		philosopher->status = THINKING;
		philosopher->times_eaten = 0;
		philosopher->last_meal_ms = params->start_time;
		philosopher->id = count;
		philosopher->meta = params;
		philosopher->order = count % 2;
	}
	return (philosopher);
}

t_fork	*init_fork(t_parameters *params, t_philosopher *owner)
{
	t_fork	*fork;

	(void) params;
	fork = malloc(sizeof(t_fork));
	if (fork != NULL)
	{
		fork->left_thread = owner;
		fork->right_thread = NULL;
		if (init_mutex(&(fork->mutex)) != 0)
		{
			free(fork);
			return (NULL);
		}
	}
	return (fork);
}

t_philosopher	*init_threads(t_parameters *params)
{
	t_philosopher	*head;
	t_philosopher	*temp;
	int				count;

	count = 1;
	head = init_philosopher(count, params);
	head->right_fork = init_fork(params, head);
	count++;
	temp = head;
	while (count <= params->philosopher_count && temp != NULL)
	{
		temp = init_and_join(temp, &count, params);
	}
	if (temp == NULL)
		return (full_clean(head));
	head->left_fork = temp->right_fork;
	temp->right_fork->right_thread = head;
	temp->next = head;
	head->last = temp;
	return (head);
}

t_philosopher	*init_and_join(t_philosopher *temp, int *count, t_parameters *params)
{
	temp->right_fork->right_thread = init_philosopher(*count, params);
	if (temp->right_fork->right_thread == NULL)
		return (NULL);
	temp->right_fork->right_thread->left_fork = temp->right_fork;
	temp->next = temp->right_fork->right_thread;
	temp = temp->next;
	temp->right_fork = init_fork(params, temp);
	if (temp->right_fork == NULL)
		return (clean_philo_return_next(temp));
	temp->last = temp->left_fork->left_thread;
	*count = *count + 1;
	return (temp);
}
