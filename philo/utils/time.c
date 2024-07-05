/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:03:08 by isemin            #+#    #+#             */
/*   Updated: 2024/07/05 11:33:43 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_from_start(t_parameters *params)
{
	int	time_now;

	time_now = time_in_ms();
	return (time_now - params->start_time);
}

int	time_without_food(int last_meal)
{
	int	time_now;

	time_now = time_in_ms();
	return (time_now - last_meal);
}

int	time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	sleep_ms(int ms)
{
	int	time_now;

	time_now = time_in_ms();
	if (ms > 5)
		usleep((ms - 5));
	while (time_in_ms() - time_now < ms)
		usleep(200);
}
