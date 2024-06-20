/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:27:44 by isemin            #+#    #+#             */
/*   Updated: 2024/06/20 20:10:25 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

# define MAX_PHILO 200

# define SLEEPING 1
# define EATING 2
# define THINKING 3
# define DEAD 0

typedef struct s_parameters {
	int	philosopher_count;
	int	time_to_die;
	int	time_to_sleep;
	int	eating_limit;
}	t_parameters;

typedef struct s_philosopher {
	pthread_t		*thread;
	t_fork			*left_fork;
	t_fork			*right_fork;
	int				status;
	int				times_eaten;
	char			*name;
	t_parameters	*meta;
}	t_philosopher;

typedef struct s_fork {
	t_philosopher	*left_thread;
	t_philosopher	*right_thread;
	pthread_mutex_t	*mutex;
}	t_fork;

#endif