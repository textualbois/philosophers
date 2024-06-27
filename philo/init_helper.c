/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 23:01:16 by isemin            #+#    #+#             */
/*   Updated: 2024/06/27 23:44:00 by isemin           ###   ########.fr       */
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

int	set_eating_limit(int argc, char **argv)
{
	if (argc == 6)
		return (ft_atoi(argv[5]));
	else
		return (-1);
}
