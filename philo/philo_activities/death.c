/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:23:32 by isemin            #+#    #+#             */
/*   Updated: 2024/06/23 19:25:05 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	has_starved(t_philosopher *philo)
{
	return (time_without_food(philo) > philo->meta->time_to_die);
}

int	philo_dead(t_philosopher *philo)
{

}