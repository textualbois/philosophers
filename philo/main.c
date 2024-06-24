/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivansemin <ivansemin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:38:33 by isemin            #+#    #+#             */
/*   Updated: 2024/06/24 01:27:11 by ivansemin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
