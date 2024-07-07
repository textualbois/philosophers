/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:27:44 by isemin            #+#    #+#             */
/*   Updated: 2024/07/07 13:19:38 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include <stdbool.h>

# define MAX_PHILO 200

# define SLEEPING 1
# define EATING 2
# define THINKING 3
# define TAKING_FORK 4
# define DEATH 0
# define GREEN 1
# define RED -1
# define ODD_NUMBER 1
# define SET 1
# define GET 2
# define TIMES_EATEN 3
# define TIMES_EATEN_THIS_ROUND 4
# define CUM_TIMES_EATEN 5
# define LAST_MEAL 6
# define SET_LAST_MEAL 7
# define FULL_COUNT 8
# define ODD_GROUP 1
# define EVEN_GROUP 0
# define LAST_GROUP 2
# define STOP 0
# define GO -1


typedef struct s_philosopher	t_philosopher;

typedef struct s_parameters {
	int				philosopher_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				cum_times_eaten;
	int				satiated_philos_count;
	int				eating_limit;
	int				ttl_eating_limit;
	int				odd_eating_threshold;
	int				even_eating_threshold;
	int				last_eating_threshold;
	int				start_time;
	int				light;
	int				times_eaten_this_round;
	pthread_mutex_t	*global_mtx;
	pthread_t		*watcher;
}	t_parameters;

typedef struct s_fork {
	t_philosopher	*left_thread;
	t_philosopher	*right_thread;
	pthread_mutex_t	*mutex;
}	t_fork;

struct s_philosopher {
	pthread_t		*thread;
	t_philosopher	*next;
	t_philosopher	*last;
	t_fork			*left_fork;
	t_fork			*right_fork;
	int				status;
	int				times_eaten;
	int				last_meal_ms;
	int				id;
	int				order;
	t_parameters	*meta;
};

// ./philo/philo_activities/philo_activities.c
void			think(t_philosopher *philo);
int				pick_up_forks(t_philosopher *philo);
void			eat(t_philosopher *philo);
void			put_down_forks(t_philosopher *philo);
void			philo_sleep(t_philosopher *philo);

// ./philo/philo_activities/fork_helpers.c
int				pick_up_from_left(t_philosopher *philo);
int				pick_up_from_right(t_philosopher *philo);

// ./philo/philo_activities/death.c
int				has_starved(t_philosopher *philo);
int				philo_dead(t_philosopher *philo);
void			*register_death(t_philosopher *philo);

// ./philo/prints/print_gate.c
void			print_action(int action, t_philosopher *philo);

// ./philo/prints/print_statements.c
void			print_thinking(t_philosopher *philo, pthread_mutex_t *print_lock);
void			print_taking_fork(t_philosopher *philo, pthread_mutex_t *print_lock);
void			print_eating(t_philosopher *philo, pthread_mutex_t *print_lock);
void			print_sleeping(t_philosopher *philo, pthread_mutex_t *print_lock);
void			print_death(t_philosopher *philo, pthread_mutex_t *print_lock);

// ./philo/routine/routine.c
void			*run_routines(t_philosopher *head);

// ./philo/utils/time.c
int				time_from_start(t_parameters *params);
int				time_without_food(int last_meal);
int				time_in_ms(void);
void			sleep_ms(int ms);

// ./philo/utils/utils.c
int				ft_isdigit(int c);
long			ft_atol(const char *nptr);
int				ft_atoi(const char *nptr);
int				get_set_value(int *val_ptr, int new_value, int get_set);

// ./philo/init.c
t_parameters	*init_parameters(int argc, char **argv);
t_philosopher	*init_philosopher(int count, t_parameters *params);
t_fork			*init_fork(t_parameters *params, t_philosopher *owner);
t_philosopher	*init_threads(t_parameters *params);
t_philosopher	*init_and_join(t_philosopher *temp, int *count, t_parameters *params);

// ./philo/init_helper.c
int				init_mutex(pthread_mutex_t **res);
int				slim_malloc(void **dst, size_t size);
int				slim_calloc(void **dst, size_t size);
void			set_eating_limits(int argc, char **argv, t_parameters *params);

// ./philo/clean/main_clean.c
t_philosopher	*clean_philo_return_previous(t_philosopher *philo);
t_philosopher	*clean_philo_return_next(t_philosopher *philo);
void			*full_clean(t_philosopher *head);
void			clean_params(t_philosopher *head);

// ./philo/get_set/time.c
int				get_set_time(int get_set, t_philosopher *philo, int	increment);

// ./philo/get_set/order.c
int				get_order(t_philosopher *philo);

// ./philo/get_set/start_stop_flags.c
int				allowed_to_continue(int	get_set, int new_val);



#endif