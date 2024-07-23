/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:23:32 by isemin            #+#    #+#             */
/*   Updated: 2024/07/23 21:35:41 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	has_starved(t_philosopher *philo)
{
	int	last_meal;

	last_meal = get_set_time(LAST_MEAL, philo, 0);
	if (last_meal == 0)
	{
		last_meal = philo->meta->start_time;
		get_set_time(SET_LAST_MEAL, philo, philo->meta->start_time);
	}
	//printf("checking starved philo %d\n", philo->id);
	return (time_without_food(last_meal) >= philo->meta->time_to_die);
}

int	philo_dead(t_philosopher *philo)
{
	print_action(DEATH, philo);
	return (0);
}

void	*register_death(t_philosopher *philo)
{
	allowed_to_continue(SET, philo->id, SHORT_LOCK);
	philo_dead(philo);
	return (NULL);
}
