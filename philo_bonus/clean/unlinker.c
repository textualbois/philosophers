/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlinker.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:48:58 by isemin            #+#    #+#             */
/*   Updated: 2024/07/04 09:56:30 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void unlink_all(void)
{
	int		i;
	char	*sem_name;

	i = 1;
	printf("unlinking philos sems\n");
	while (i <= 200)
	{
	//	printf("before sem_name\n");
		sem_name = create_sem_name(i);
	//	printf("##########before unlink############\n");
		//fflush(stdout);
		sem_unlink(sem_name);
		//printf("after unlink\n");
	//	fflush(stdout);
		free(sem_name);
		i++;
	}

	printf("Unlinking semaphore /forks\n");
	sem_unlink("/forks");

	printf("Unlinking semaphore /death_watcher\n");
	sem_unlink("/death_watcher");

	printf("Unlinking semaphore /print\n");
	sem_unlink("/print");

	printf("Unlinking semaphore /time\n");
	sem_unlink("/time");

	printf("Unlinking semaphore /death\n");
	sem_unlink("/death");
}
