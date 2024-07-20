/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bouncer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:01:30 by isemin            #+#    #+#             */
/*   Updated: 2024/07/20 20:22:51 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	kick_them_out(t_parameters *params)
{
	kill_kids(&params->kids, params->philo_count - 1, 0);
}

void	*bouncer_routine(void *data)
{
	t_parameters	*params;
	int				i;

	i = 0;
	params = (t_parameters *)data;
	params->bouncer_sem = \
		sem_open("/bouncer", O_CREAT, 0644, params->philo_count);
	if (params->bouncer_sem == SEM_FAILED)
		exit(1);
	while (i <= params->philo_count)
	{
		sem_wait(params->bouncer_sem);
		i++;
	}
	r_u_full(params);
	return (NULL);
}

void	r_u_full(t_parameters *params)
{
	sem_wait(params->bouncer_sem);
	sem_wait(params->printer);
	kick_them_out(params);
	sem_post(params->printer);
	sem_post(params->bouncer_sem);
	sem_close(params->bouncer_sem);
	sem_unlink("/bouncer");
}
