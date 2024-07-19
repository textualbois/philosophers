/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 23:01:16 by isemin            #+#    #+#             */
/*   Updated: 2024/07/19 23:23:04 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*create_sem_name(int id)
{
	char	*id_str;
	char	*res;

	id_str = ft_itoa(id);
	if (id_str != NULL)
	{
		res = ft_strjoin("/philo_", id_str);
		if (res != NULL)
		{
			free(id_str);
			return (res);
		}
		free(id_str);
	}
	return (NULL);
}

int	init_semaphore(sem_t **sem, const char *name, int init_value)
{
	*sem = sem_open(name, O_CREAT | O_EXCL, 0644, init_value);
	if (*sem == SEM_FAILED)
	{
		printf("sem %s failed\n", name);
		return (1);
	}
	return (0);
}

int	slim_malloc(void **dst, size_t size)
{
	*dst = malloc(size);
	if (*dst != NULL)
		return (0);
	return (1);
}

int	slim_calloc(void **dst, size_t size)
{
	*dst = malloc(size);
	if (*dst == NULL)
		return (1);
	memset(*dst, 0, size);
	return (0);
}

void	set_eating_limits(int argc, char **argv, t_parameters *params)
{
	if (argc == 6)
	{
		params->eating_limit = ft_atoi(argv[5]);
		params->ttl_eating_limit = params->eating_limit * params->philo_count;
	}
	else
	{
		params->eating_limit = -1;
		params->ttl_eating_limit = -1;
	}
}
