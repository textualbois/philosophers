/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:01:43 by isemin            #+#    #+#             */
/*   Updated: 2024/07/03 11:59:45 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	get_set_time(int get_set, t_philosopher *philo, int	increment)
{
	int	res;

	// printf("getting or setting time\nwaiting for sem /philo_%i\n", philo->id);
	// fflush(stdout);
	sem_wait(philo->sem);
	// printf("acquired sem /philo_%i\n", philo->id);
	// fflush(stdout);
	res = 0;
	if (get_set == TIMES_EATEN_THIS_ROUND)
		res = philo->meta->times_eaten_this_round;
	else if (get_set == SET)
		philo->times_eaten += increment;
	else if (get_set == CUM_TIMES_EATEN)
		res = philo->meta->cum_times_eaten;
	else if (get_set == TIMES_EATEN)
		res = philo->times_eaten;
	sem_post(philo->sem);
	// printf("released sem /philo_%i\n", philo->id);
	// fflush(stdout);
	return (res);
}

