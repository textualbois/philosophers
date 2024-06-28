/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivansemin <ivansemin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:23:32 by isemin            #+#    #+#             */
/*   Updated: 2024/06/28 20:22:24 by ivansemin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	has_starved(t_philosopher *philo)
{
	if (philo->last_meal_ms == 0)
		philo->last_meal_ms = philo->meta->start_time;
	return (time_without_food(philo) > philo->meta->time_to_die);
}

int	philo_dead(t_philosopher *philo)
{
	print_action(DEATH, philo);
	return (0);
}
