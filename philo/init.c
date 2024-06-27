/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivansemin <ivansemin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:01:53 by isemin            #+#    #+#             */
/*   Updated: 2024/06/26 18:04:48 by ivansemin        ###   ########.fr       */
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

	params = calloc(1, sizeof(t_parameters));
	if (params != NULL)
	{
		params->philosopher_count = ft_atoi(argv[1]);
		params->time_to_die = ft_atoi(argv[2]);
		params->time_to_eat = ft_atoi(argv[3]);
		params->time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			params->eating_limit = ft_atoi(argv[5]);
		else
			params->eating_limit = -1;
		params->light = GREEN;
		params->start_time = time_in_ms();
		params->global_mtx = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(params->global_mtx, NULL);
		params->watcher = malloc(sizeof(pthread_t));
	}
	return (params);
}

t_philosopher	*init_philosopher(int count, t_parameters *params)
{
	t_philosopher	*philosopher;

	philosopher = malloc(sizeof(t_philosopher));
	if (philosopher != NULL)
	{
		philosopher->thread = calloc(1, sizeof(pthread_t));
		philosopher->left_fork = NULL;
		philosopher->right_fork = NULL;
		philosopher->status = THINKING;
		philosopher->times_eaten = 0;
		philosopher->last_meal_ms = params->start_time;
		philosopher->id = count;
		philosopher->meta = params;
	}
	//printf("philo light = %i, %s\n", philosopher->meta->light, philosopher->meta->light == GREEN ? "GREEN" : "RED");
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
		fork->mutex = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(fork->mutex, NULL);
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
	while (count <= params->philosopher_count)
	{
		temp->right_fork->right_thread = init_philosopher(count, params);
		temp->right_fork->right_thread->left_fork = temp->right_fork;
		temp->next = temp->right_fork->right_thread;
		temp = temp->next;
		temp->right_fork = init_fork(params, temp);
		temp->last = temp->left_fork->left_thread;
		count++;
	}
	head->left_fork = temp->right_fork;
	temp->right_fork->right_thread = head;
	temp->next = head;
	head->last = temp;
	return (head);
}
