/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:27:44 by isemin            #+#    #+#             */
/*   Updated: 2024/07/04 10:01:47 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <string.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <stdbool.h>
# include <fcntl.h>

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
# define ODD_GROUP 1
# define EVEN_GROUP 0
# define LAST_GROUP 2
# define CHILD 0
# define FORK_ERROR 3

typedef struct s_philosopher	t_philosopher;

typedef struct s_parameters {
	int				philosopher_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				cum_times_eaten;
	int				eating_limit;
	int				ttl_eating_limit;
	int				start_time;
	int				light;
	int				times_eaten_this_round;
	sem_t			*time;
	sem_t			*death_watcher;
	sem_t			*printer;
	sem_t			*forks;
	pthread_t		*watcher;
}	t_parameters;

struct s_philosopher {
	sem_t			*sem;
	int				status;
	int				times_eaten;
	int				last_meal_ms;
	int				id;
	int				order;
	t_parameters	*meta;
};

// ./philo/clean/main_clean.c
int 			kill_kids(pid_t **kids, int start_from);
t_philosopher	*clean_philo_return_previous(t_philosopher *philo);
t_philosopher	*clean_philo_return_next(t_philosopher *philo);
void			*full_clean(t_philosopher *head);
int				clean_sems(t_parameters *parameters);

// ./philo/clean/clean_helper.c
void			destroy_semaphore(sem_t *sem, const char *name);
void			clean_params(t_parameters **params);

// ./philo/clean/unlinker.c
void 			unlink_all(void);

// ./philo/get_set/time.c
int				get_set_time(int get_set, t_philosopher *philo, int	increment);

// ./philo/get_set/order.c
int				get_order(t_philosopher *philo);

// ./philo/philo_activities/death.c
int				has_starved(t_philosopher *philo);
int				philo_dead(t_philosopher *philo);
void			*register_death(t_philosopher *philo);
int				any_deaths(sem_t *lock);

// ./philo/philo_activities/eating_helpers.c
int				philo_full(t_philosopher *philo);

// ./philo/philo_activities/philo_activities.c
void			think(t_philosopher *philo);
void			pick_up_forks(t_philosopher *philo);
void			eat(t_philosopher *philo);
void			put_down_forks(t_philosopher *philo);
void			philo_sleep(t_philosopher *philo);

// ./philo/prints/print_gate.c
void			print_action(int action, t_philosopher *philo);

// ./philo/prints/print_statements.c
void			print_thinking(t_philosopher *philo);
void			print_taking_fork(t_philosopher *philo);
void			print_eating(t_philosopher *philo);
void			print_sleeping(t_philosopher *philo);
void			print_death(t_philosopher *philo);

// ./philo/routine/routine.c
int				run_routines(t_parameters *params);

// ./philo/utils/str.c
size_t			ft_strlen(const char *s);
char			*ft_itoa(int n);
char			*ft_strjoin(char *s1, char *s2);
int				ft_num_digits(long n);

// ./philo/utils/time.c
int				time_from_start(t_parameters *params);
int				time_without_food(t_philosopher *philo);
int				time_in_ms(void);
void			sleep_ms(int ms);

// ./philo/utils/utils.c
int				ft_isdigit(int c);
long			ft_atol(const char *nptr);
int				ft_atoi(const char *nptr);
int				get_set_value(int *val_ptr, int new_value, int get_set);

// ./philo/init_helper.c
char			*create_sem_name(int id);
int				init_semaphore(sem_t **sem, const char *name, int init_value);
int				slim_malloc(void **dst, size_t size);
int				slim_calloc(void **dst, size_t size);
void			set_eating_limits(int argc, char **argv, t_parameters *params);

// ./philo/init.c
t_parameters	*init_parameters(int argc, char **argv);
t_philosopher	*init_philosopher(int count, t_parameters *params);
t_philosopher	*init_threads(t_parameters *params);
t_philosopher	*init_and_join(t_philosopher *temp, int *count, t_parameters *params);
int				init_main_semaphores(t_parameters *params);


#endif