/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivansemin <ivansemin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 01:55:21 by ivansemin         #+#    #+#             */
/*   Updated: 2024/06/23 02:17:26 by ivansemin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	think(t_philosopher *philo)
{
	printf("%i %s is thinking\n", time, philo->name);
}

void	pick_up_forks(t_philosopher *philo)
{
	//if (philo->name[0] == '1' && philo->name[1] == '\0')
	if (time_now - philo->last_meal_ms > philo->meta->time_to_die)
		philo_dead(philo);
	

}

void	eat(t_philosopher *philo)
{
	usleep(philo->meta->time_to_eat);
	philo->times_eaten += 1;
}

void	put_down_forks(t_philosopher *philo)
{

}

void	sleep(t_philosopher *philo)
{

}
