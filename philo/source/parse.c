#include "../includes/philo.h"

void init_struct(t_param *param, t_philo *philo)
{
	//philo->param = NULL;
	philo->name = 0;
	philo->meals = 0;
	philo->last_meal = 0;
	//philo->death = false;
	philo->satisfied = false;
	philo->times_eat = 0;
	philo->fork_left = 0;
	philo->fork_right = 0;
	param->who_dead = 0;
	//param->exit = false;
	param->philo_nbr = 0;
	param->t_todie = 0;
	param->t_toeat = 0;
	param->t_tosleep = 0;
	param->meals_nbr = 0;
	param->start_time = 0;
	// printf("philo_name: %i\n", philo->name);
	// printf("philo_nbr: %i\n", philo->param->philo_nbr);
	// printf("time_die: %i\n", philo->param->t_todie);
	// printf("time_eat: %i\n", philo->param->t_toeat);
	// printf("time_sleep: %i\n", philo->param->t_tosleep);
}

void	get_paramm(char *argv[], t_param *param)
{
	int i;

	i = 0;
	param->philo_nbr = ft_atoi(argv[1]);
	param->t_todie = ft_atoi(argv[2]);
	//printf("apos guardar o valor, t_todie tem %i\n",param->t_todie);
	param->t_toeat = ft_atoi(argv[3]);
	param->t_tosleep = ft_atoi(argv[4]);
	if (argv[5])
		param->meals_nbr = ft_atoi(argv[5]);
	else
		param->meals_nbr = 0;
	param->start_time = phil_clockins();
	param->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (param->philo_nbr + 32));
	while (i < param->philo_nbr)
	{
		pthread_mutex_init(&param->forks[i], NULL);
		i++;
	}
	//printf("Deu bom em %d :D\n", time->tv_usec);
	//printf("em segundos: %li\n", param->start_time);
}