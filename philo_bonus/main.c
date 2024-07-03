/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:38:33 by isemin            #+#    #+#             */
/*   Updated: 2024/07/03 13:27:29 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	bad_input(int argc, char **argv)
{
	int i;
	int	p;

	if (argc == 5 || argc == 6)
	{
		i = 1;
		while (i < argc)
		{
			p = 0;
			while(argv[i][p] != '\0')
			{
				if (ft_isdigit((int)argv[i][p]) == 0)
				{
					printf("Bad input.\nUse only ints\n");
					return (1);
				}
				p++;
			}
			i++;
		}
		return (0);
	}
	printf("Bad input.\nUsage:\n./philo philo_count time_to_die");
	printf(" time_to_eat time_to_sleep [meal_limit(optional)]\n");
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
	int				res;

	unlink_all();
	printf("main\n");
	fflush(stdout);
	if (bad_input(argc, argv))
		return (1);
	params = init_parameters(argc, argv);
	if (params != NULL)
	{
		printf("params good\n");
		fflush(stdout);
		res = run_routines(params); //FIHURE OUT RETURN VALS
		if (res == 1)
		{
			clean_params(&params); //todo
			return (1);
		}
	}
	else
		return (1);
	clean_params(&params);
	return (0);
}
