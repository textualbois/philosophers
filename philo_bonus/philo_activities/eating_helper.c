/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 05:19:35 by isemin            #+#    #+#             */
/*   Updated: 2024/07/19 17:18:17 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philo_full(t_philosopher *philo)
{
	if (philo->meta->eating_limit == -1)
		return (false);
	else
		return (philo->times_eaten >= philo->meta->eating_limit);
}

void	is_philo_full(t_philosopher *philo)
{
	if (philo->times_eaten == philo->meta->eating_limit)
		sem_post(philo->meta->bouncer_sem);
}
