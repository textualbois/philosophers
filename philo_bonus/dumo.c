#include "philo_bonus.h"

# define WRONG_INPUT 1
# define MALLOC_ERROR 2
# define FORK_ERROR 3
# define SEM_ERROR 4
# define THREAD_ERROR 4

typedef struct s_philo
{
	int				id;
	int				nb_meals_had;
	struct s_data	*data;
	t_state			state;
	u_int64_t		last_eat_time;
	sem_t			*sem_philo;
}t_philo;

typedef struct s_data
{
	int				nb_philos;
	int				nb_meals;
	u_int64_t		eat_time;
	u_int64_t		die_time;
	u_int64_t		sleep_time;
	u_int64_t		start_time;
	sem_t			*sem_forks;
	sem_t			*sem_print;
	pthread_t		monitor;
	t_philo			philo;
}t_data;

int	philosophers_bonus(int argc, char **argv)
{
	t_data	data;

	if (init_data(&data, argc, argv) != 0)
		return (WRONG_INPUT);
	run_processes(&data);
	clean_up(&data);
	return (0);
}

int	run_processes(t_data *data) //forks all of the the pricesses
{
	pid_t	p_id;
	int		i;

	i = 0;
	data->start_time = get_time();
	while (i++ < data->nb_philos)
	{
		p_id = fork();
		if (p_id == 0) //in child proccess
		{
			start_routine(data, i);	//
		}
		else if (p_id == -1)
			return (FORK_ERROR);
	}
	p_id = waitpid(0, NULL, 0);
	while (p_id != -1)
		p_id = waitpid(0, NULL, 0);
	return (0);
}

int	start_routine(t_data *data, int id) //process for each seperate philo
{
	if (set_philo(data, id)) // i dont think i need a sem for each philo
		exit(1);
	sleep_if_id_is_even(data);
	if (pthread_create(&data->monitor, NULL, &monitor_death, data)) // so inside each process you start a seperate thread
		return (THREAD_ERROR);
	while (true)
	{
		if (eat(data) || should_stop(get_philo_state(data)))
		{
			break ;
		}
		if (ft_sleep(data) || should_stop(get_philo_state(data)))
		{
			break ;
		}
		if (think(data))
		{
			break ;
		}
	}
	if (pthread_join(data->monitor, NULL))
		exit(1);
	sem_close(data->philo.sem_philo);
	exit(0);
}

int	set_philo(t_data *data, int id) // i dont think i need this.
{
	char	*sem_name;

	sem_name = create_sem_name(id);
	if (sem_name == NULL)
		exit(MALLOC_ERROR);
	sem_unlink(sem_name);
	data->philo.sem_philo = sem_open(sem_name, O_CREAT, 0644, 1);
	sem_unlink(sem_name);
	free(sem_name);
	data->philo.id = id;
	update_last_meal_time(data);
	return (0);
}

void	*monitor_death(void *data_p)
{
	t_data	*data;

	data = (t_data *)data_p;
	while (should_stop(get_philo_state(data)) == false)
	{
		if (someone_died())
			return (set_philo_state(data, FINISH), NULL);
		if (philo_died(data))
		{
			sem_wait(data->sem_print);
			if (philo_died(data) && someone_died() == false)
			{
				set_philo_state(data, DEAD);
				let_others_know();
				printf("%llu %d %s\n", get_time() - get_start_time(data),
					data->philo.id, DIED);
				sem_post(data->sem_print);
				break ;
			}
			sem_post(data->sem_print);
		}
		usleep(1000);
	}
	return (NULL);
}