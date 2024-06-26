/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 23:01:16 by isemin            #+#    #+#             */
/*   Updated: 2024/07/01 04:46:28 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(pthread_mutex_t **res)
{
	*res = malloc(sizeof(pthread_mutex_t));
	if (*res == NULL)
		return (1);
	else if (pthread_mutex_init(*res, NULL) != 0)
	{
		free(*res);
		*res = NULL;
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
		params->ttl_eating_limit = params->eating_limit * params->philosopher_count;
	}
	else
	{
		params->eating_limit = -1;
		params->ttl_eating_limit = -1;
	}
	params->odd_eating_threshold = params->philosopher_count / 2;
	params->even_eating_threshold = params->odd_eating_threshold * 2;
	params->last_eating_threshold = params->philosopher_count;

	// printf("%i philo_count\n%i eating_limit\n%i ttl_eating_limit\n%i odd_eating_threshold\n%i even_eating_threashold\n%i last_eating_threshold\n%i times_eaten_this_round\n\n", \
	// params->philosopher_count, params->eating_limit, params->ttl_eating_limit, params->odd_eating_threshold, params->even_eating_threshold, params->last_eating_threshold, params->times_eaten_this_round);
}
