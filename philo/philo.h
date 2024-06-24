/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivansemin <ivansemin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:27:44 by isemin            #+#    #+#             */
/*   Updated: 2024/06/24 03:15:42 by ivansemin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define MAX_PHILO 200

# define SLEEPING 1
# define EATING 2
# define THINKING 3
# define TAKING_FORK 4
# define DEATH 0

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
	int				id;
	t_parameters	*meta;
}	t_philosopher;

typedef struct s_fork {
	t_philosopher	*left_thread;
	t_philosopher	*right_thread;
	pthread_mutex_t	*mutex;
}	t_fork;

// ./philo/philo_activities/philo_activities.c
void			think(t_philosopher *philo);
void			pick_up_forks(t_philosopher *philo);
void			eat(t_philosopher *philo);
void			put_down_forks(t_philosopher *philo);
void			sleep(t_philosopher *philo);

// ./philo/philo_activities/death.c
int				has_starved(t_philosopher *philo);
int				philo_dead(t_philosopher *philo);

// ./philo/prints/print_gate.c
void			print_action(int action, t_philosopher *philo);

// ./philo/prints/print_statements.c
void			print_thinking(t_philosopher *philo);
void			print_taking_fork(t_philosopher *philo);
void			print_eating(t_philosopher *philo);
void			print_sleeping(t_philosopher *philo);
void			print_death(t_philosopher *philo);

// ./philo/routine/routine.c
void			run_routines(t_philosopher *head);

// ./philo/init.c
t_parameters	*init_parameters(int argc, char **argv);
t_philosopher	*init_philosopher(int count, t_parameters *params);
t_fork			*init_fork(t_parameters *params, t_philosopher *owner);
t_philosopher	*init_threads(t_parameters *params);

#endif