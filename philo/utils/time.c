/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:03:08 by isemin            #+#    #+#             */
/*   Updated: 2024/06/23 19:20:35 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	time_from_start(t_parameters *params)
{
	return (gettimeofday(NULL, NULL) - params->start_time);
}

long	time_without_food(t_philosopher *philo)
{
	return (gettimeofday(NULL, NULL) - philo->last_meal_ms);
}
