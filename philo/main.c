/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:38:33 by isemin            #+#    #+#             */
/*   Updated: 2024/07/19 23:42:54 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	extra_check(int argc, char **argv)
{
	if (ft_atoi(argv[1]) > 200 || ft_atoi(argv[1]) < 1)
	{
		printf("Wrong philo count\n 0 < philo count <= 200\n");
		return (1);
	}
	if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
	{
		printf("Wrong main parameter value\n try >= 60\n");
		return (1);
	}
	if (argc == 6 && ft_atoi(argv[5]) < 0)
	{
		printf("wrong minimum meal count value\n try a non-negative value\n");
		return (1);
	}
	return (0);
}

static int	bad_input(int argc, char **argv)
{
	int	i;
	int	p;

	if (argc == 5 || argc == 6)
	{
		i = 1;
		while (i < argc)
		{
			p = 0;
			while (argv[i][p] != '\0')
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
		return (extra_check(argc, argv));
	}
	printf("Bad input.\nUsage:\n./philo philo_count time_to_die");
	printf(" time_to_eat time_to_sleep [meal_limit(optional)]\n");
	return (1);
}

/** * @brief spwans threads (philosophers) that
 * interact with each other certain parameters
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
	int				*res;

	res = NULL;
	head = NULL;
	if (bad_input(argc, argv))
		return (1);
	params = init_parameters(argc, argv);
	if (params != NULL)
	{
		head = init_threads(params);
		if (head != NULL)
		{
			res = run_routines(head);
			if (res == NULL)
				full_clean(head);
		}
		else
			return (1);
	}
	else
		return (1);
	return (0);
}
