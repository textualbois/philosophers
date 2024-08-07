/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_stop_flags.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:07:38 by isemin            #+#    #+#             */
/*   Updated: 2024/07/23 17:36:17 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allowed_to_continue(int get_set, int new_val, int modifier)
{
	static pthread_mutex_t	light_checker = PTHREAD_MUTEX_INITIALIZER;
	static int				go_stop;
	int						res;

	if (modifier != RELEASE_LOCK)
	{
		pthread_mutex_lock(&light_checker);
		if (get_set == GET)
			res = go_stop;
		else if (get_set == SET)
		{
			go_stop = new_val;
			res = go_stop;
		}
		else
			res = -1;
		if (modifier != LONG_LOCK)
			pthread_mutex_unlock(&light_checker);
		return (res);
	}
	pthread_mutex_unlock(&light_checker);
	return (0);
}
