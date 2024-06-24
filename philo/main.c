/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:38:33 by isemin            #+#    #+#             */
/*   Updated: 2024/06/25 00:08:31 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	bad_input(int argc, char **argv)
{
	if (argc > 4 && argv[3] != NULL)
		return (0);
	else
		return (1);
}

/**
 * @brief spwans threads (philosophers) that interact with each other certain parameters
 *
 * @param argc
 * @param argv[1] number_of_philosophers
 * @param argv[2] time_to_die
 * @param argv[3] time_to_eat
 * @param argv[4] time_to_sleep
 * @param argv[5] eating_limit (optional)
 * @return int
 */
int	main(int argc, char **argv)
{
	t_parameters	*params;
	t_philosopher	*head;

	if (bad_input(argc, argv))
		return (1);
	params = init_parameters(argc, argv);
	head = init_threads(params);
	run_routines(head);

}
