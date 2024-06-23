/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:27:44 by isemin            #+#    #+#             */
/*   Updated: 2024/06/23 19:18:16 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>

# define MAX_PHILO 200

# define SLEEPING 1
# define EATING 2
# define THINKING 3
# define TAKING_FORK 4
# define DEAD 0

typedef struct s_parameters {
	long	philosopher_count;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	eating_limit;
	long	start_time;
}	t_parameters;

typedef struct s_philosopher {
	pthread_t		*thread;
	t_fork			*left_fork;
	t_fork			*right_fork;
	int				status;
	int				times_eaten;
	long			last_meal_ms;
	int				name;
	t_parameters	*meta;
}	t_philosopher;

typedef struct s_fork {
	t_philosopher	*left_thread;
	t_philosopher	*right_thread;
	pthread_mutex_t	*mutex;
}	t_fork;

#endif