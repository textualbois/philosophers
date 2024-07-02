/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:01:43 by isemin            #+#    #+#             */
/*   Updated: 2024/07/01 12:04:20 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_set_time(int get_set, t_philosopher *philo, int	increment)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	int						res;

	pthread_mutex_lock(&mutex);
	res = 0;
	if (get_set == TIMES_EATEN_THIS_ROUND)
		res = philo->meta->times_eaten_this_round;
	else if (get_set == SET)
	{
		philo->times_eaten += increment;
		philo->meta->times_eaten_this_round += increment;
		philo->meta->cum_times_eaten += increment;
		if (philo->meta->times_eaten_this_round == \
			philo->meta->last_eating_threshold)
			philo->meta->times_eaten_this_round = 0;
	}
	else if (get_set == CUM_TIMES_EATEN)
		res = philo->meta->cum_times_eaten;
	else if (get_set == TIMES_EATEN)
		res = philo->times_eaten;
	pthread_mutex_unlock(&mutex);
	return (res);
}
