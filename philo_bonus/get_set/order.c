/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:48:10 by isemin            #+#    #+#             */
/*   Updated: 2024/07/03 08:07:30 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// int	get_order(t_philosopher *philo)
// {
// 	int	times_eaten;

// 	times_eaten = get_set_time(TIMES_EATEN_THIS_ROUND, philo, 0);
// 	if (times_eaten < philo->meta->odd_eating_threshold)
// 		return (ODD_GROUP);
// 	else if (philo->meta->even_eating_threshold == philo->meta->last_eating_threshold)
// 	{
// 		return (EVEN_GROUP);
// 	}
// 	else if (times_eaten + 1 == philo->meta->last_eating_threshold)
// 		return (LAST_GROUP);
// 	else
// 		return (EVEN_GROUP);
// }
