/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:03:08 by isemin            #+#    #+#             */
/*   Updated: 2024/07/04 07:00:48 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	time_from_start(t_parameters *params)
{
	int	time_now;

	time_now = time_in_ms();
	return (time_now - params->start_time);
}

int	time_without_food(t_philosopher *philo)
{
	int	time_now;
	int last_meal;

	sem_wait(philo->sem);
	// printf("under philo->sem lock to get last meal time\n");
	// fflush(stdout);
	last_meal = philo->last_meal_ms;
	sem_post(philo->sem);
	// printf("releasing philo->sem lock after getting last meal time\n");
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
