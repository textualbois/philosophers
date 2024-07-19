/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bouncer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:01:30 by isemin            #+#    #+#             */
/*   Updated: 2024/07/19 18:12:42 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	kick_them_out(t_parameters *params)
{
	kill_kids(&params->kids, params->philosopher_count - 1);
	printf("kids are dead\n");
}

void	*bouncer_routine(void *data)
{
	t_parameters	*params;
	int				i;
	printf("bouncer is here 1/2\n");

	i = 0;
	params = (t_parameters *)data;
	printf("bouncer is here 2/2\nphilo_count is %i\n", params->philosopher_count);
	params->bouncer_sem = sem_open("/bouncer", O_CREAT, 0644, params->philosopher_count);
	if (params->bouncer_sem == SEM_FAILED)
	{
		printf("sem_open failed\n");
		exit(1);
	}
	printf("bouncer is open\n");
	while(i < params->philosopher_count)
	{
		sem_wait(params->bouncer_sem);
		i++;
	}
	printf("we locked and loaded\n");
	r_u_full(params);
	return (NULL);
}

void	r_u_full(t_parameters *params)
{
	sem_wait(params->bouncer_sem); //this will open when only each philo signals sem_open
	printf("all should be full\n");
	sem_wait(params->printer);
	printf("all should stop reporting\n");
	kick_them_out(params);
	sem_post(params->printer);
	sem_post(params->bouncer_sem);
	sem_close(params->bouncer_sem);
	sem_unlink("/bouncer");
}
