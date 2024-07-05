/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_stop_flags.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:07:38 by isemin            #+#    #+#             */
/*   Updated: 2024/07/05 12:29:03 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allowed_to_continue(int	get_set, int new_val)
{
	static pthread_mutex_t	light_checker = PTHREAD_MUTEX_INITIALIZER;
	static int				go_stop;
	int						res;

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
	pthread_mutex_unlock(&light_checker);
	return (res);
}
