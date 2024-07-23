/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:01:43 by isemin            #+#    #+#             */
/*   Updated: 2024/07/23 21:56:44 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	incr_times_eaten(t_philosopher *philo, int increment)
{
	philo->times_eaten += increment;
	philo->meta->times_eaten_this_round += increment;
	philo->meta->cum_times_eaten += increment;
	if (philo->meta->times_eaten_this_round == \
		philo->meta->last_eating_threshold)
		philo->meta->times_eaten_this_round = 0;
	if (philo->times_eaten == philo->meta->eating_limit)
		philo->meta->satiated_philos_count++;
	if (philo->meta->eating_limit == 0)
		philo->meta->satiated_philos_count++;
}

int	get_set_time(int get_set, t_philosopher *philo, int increment)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	int						res;

	pthread_mutex_lock(&mutex);
	res = 0;
	if (get_set == LAST_MEAL)
		res = philo->last_meal_ms;
	else if (get_set == TIMES_EATEN_THIS_ROUND)
		res = philo->meta->times_eaten_this_round;
	else if (get_set == SET)
		philo->last_meal_ms = time_in_ms();
	else if (get_set == INCR_TIMES_EATEN)
		incr_times_eaten(philo, increment);
	else if (get_set == FULL_COUNT)
		res = philo->meta->satiated_philos_count;
	else if (get_set == CUM_TIMES_EATEN)
		res = philo->meta->cum_times_eaten;
	else if (get_set == TIMES_EATEN)
		res = philo->times_eaten;
	else if (get_set == SET_LAST_MEAL)
		philo->last_meal_ms = philo->meta->start_time;
	pthread_mutex_unlock(&mutex);
	return (res);
}
