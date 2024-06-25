/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:27:44 by isemin            #+#    #+#             */
/*   Updated: 2024/06/25 20:15:28 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>


# define MAX_PHILO 200

# define SLEEPING 1
# define EATING 2
# define THINKING 3
# define TAKING_FORK 4
# define DEATH 0
# define GREEN 1
# define RED -1

typedef struct s_philosopher	t_philosopher;

typedef struct s_parameters {
	int				philosopher_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eating_limit;
	int				start_time;
	int				light;
	pthread_mutex_t	*global_mtx;
}	t_parameters;

typedef struct s_fork {
	t_philosopher	*left_thread;
	t_philosopher	*right_thread;
	pthread_mutex_t	*mutex;
}	t_fork;

struct s_philosopher {
	pthread_t		*thread;
	t_fork			*left_fork;
	t_fork			*right_fork;
	int				status;
	int				times_eaten;
	int				last_meal_ms;
	int				id;
	t_parameters	*meta;
};

// ./philo/philo_activities/philo_activities.c
void			think(t_philosopher *philo);
void			pick_up_forks(t_philosopher *philo);
void			eat(t_philosopher *philo);
void			put_down_forks(t_philosopher *philo);
void			philo_sleep(t_philosopher *philo);

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

// ./philo/utils/time.c
int				time_from_start(t_parameters *params);
int				time_without_food(t_philosopher *philo);
int				time_in_ms(void);
void			sleep_ms(int ms);

// ./philo/utils/utils.c
int				ft_isdigit(int c);
long			ft_atol(const char *nptr);
int				ft_atoi(const char *nptr);

// ./philo/init.c
t_parameters	*init_parameters(int argc, char **argv);
t_philosopher	*init_philosopher(int count, t_parameters *params);
t_fork			*init_fork(t_parameters *params, t_philosopher *owner);
t_philosopher	*init_threads(t_parameters *params);

#endif