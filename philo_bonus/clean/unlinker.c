/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlinker.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:48:58 by isemin            #+#    #+#             */
/*   Updated: 2024/07/07 14:04:44 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void unlink_all(void)
{
	int		i;
	char	*sem_name;

	i = 1;
	while (i <= 200)
	{
		sem_name = create_sem_name(i);
		sem_unlink(sem_name);
		free(sem_name);
		i++;
	}
	sem_unlink("/forks");
	sem_unlink("/death_watcher");
	sem_unlink("/print");
	sem_unlink("/time");
	sem_unlink("/death");
}
