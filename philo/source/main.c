#include "../includes/philo.h"

static int	validate_args(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments.\n");
		return (1);
	}
	return (0);
}

static int	entry_args_check(int argc, char *argv[])
{
	int i;
	long int temp;

	i = 1;
	temp = 0;
	argc--;
	while (i <= argc)
	{
		if (!ft_isdigit(*argv[i]))
		{
			printf("Error: arguments must be all digits.\n");
			return(1);
		}
		temp = ft_atoi(argv[i]);
		if (!temp)
		{
			printf("Error: arguments must be integers.\n");
			return(1);
		}
		i++;
	}
	return (0);
}

void	only_onephilo(t_philo *one)
{
	printf("%ld %i has taken a fork\n", time_calc(one->params->start_time), one->name);
	//printf("In %ld miliseconds %i has taken a fork\n", time_calc(one->params->start_time), one->name);
	usleep(one->params->t_todie * 1000);
	printf("%ld %i died\n", time_calc(one->params->start_time), one->name);
	//printf("In %ld miliseconds %i died\n", time_calc(one->params->start_time), one->name);
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->params->forks[philo->fork_left]);
	if (philo->params->who_dead != 0)
		return (1);
	//printf("In %ld miliseconds %i has taken a fork\n", time_calc(philo->params->start_time), philo->name);
	printf("\033[0;32m%ld %i has taken the left fork\n\033[0m", time_calc(philo->params->start_time), philo->name);
	pthread_mutex_lock(&philo->params->forks[philo->fork_right]);
	if (philo->params->who_dead != 0)
		return (1);
	/* printf("In %ld miliseconds %i has taken a fork\n", time_calc(philo->params->start_time), philo->name);
	printf("In %ld miliseconds %i is eating\n", time_calc(philo->params->start_time), philo->name); */
	printf("\033[0;35m%ld %i has taken the right fork\n\033[0m", time_calc(philo->params->start_time), philo->name);
	if (philo->params->who_dead != 0)
		return (1);
	printf("\033[0;33m%ld %i is eating\n\033[0m", time_calc(philo->params->start_time), philo->name);
	philo->last_meal = phil_clockins();
	//philo->last_meal = time_calc(philo->params->start_time);
	//printf("%i 's last meal was in: %li", philo->name, philo->last_meal);
	philo->meals++;
	//printf("In %ld miliseconds %i meals\n", time_calc(philo->params->start_time), philo->meals);
	if (philo->params->who_dead != 0)
		return (1);
	usleep(philo->params->t_toeat * 1000);
	pthread_mutex_unlock(&philo->params->forks[philo->fork_right]);
	pthread_mutex_unlock(&philo->params->forks[philo->fork_left]);
	return (0);
}

int	sleeping(t_philo *philo)
{
	if (philo->params->who_dead != 0)
		return (1);
	printf("%ld %i is sleeping\n", time_calc(philo->params->start_time), philo->name);
	//printf("In %ld miliseconds %i is sleeping\n", time_calc(philo->params->start_time), philo->name);
	usleep(philo->params->t_tosleep * 1000);
	return (0);
}

int	thinking(t_philo *philo)
{
	if (philo->params->who_dead != 0)
		return (1);
	printf("\033[0;31m%ld %i is thinking\n\033[0m", time_calc(philo->params->start_time), philo->name);
	//printf("In %ld %i is thinking\n", time_calc(philo->params->start_time), philo->name);
	return (0);
}

int	routine(t_philo *philo)
{
	if(eating(philo) == 1 || philo->satisfied == true)
		return (1);
	if(sleeping(philo) == 1 || philo->satisfied == true)
		return (1);
	if(thinking(philo) == 1 || philo->satisfied == true)
		return (1);
	return (0);
}

int		verify(t_philo *philo)
{
	if (philo->params->who_dead != 0)
		return (1);
	if (philo->params->meals_nbr != 0)
		if (philo->meals == philo->params->meals_nbr)
		{
			philo->satisfied = true;
			return (1);
		}
	if (time_if_died(philo->params->t_todie, philo->last_meal) == 0)
		{
			pthread_mutex_lock(&philo->params->dead);
			if (philo->params->who_dead == 0)
			{
				philo->params->who_dead = philo->name;
				printf("\033[0;31m%ld %i died\n\033[0m", time_calc(philo->params->start_time), philo->name);
			}
			pthread_mutex_unlock(&philo->params->dead);
			return (1);
		}
	return (0);
}

void	*end_dinner(void *phi)
{
	t_philo *philo;

	philo = (t_philo *)phi;
	while (!verify(philo))
		continue ;
	return (NULL);
}

void	*dinner(void *arg)
{
	pthread_t waiter;
	t_philo	*caio;

	caio = NULL;
	caio = (t_philo *)arg;
	if (caio->params->philo_nbr == 1)
	{
		only_onephilo(caio);
		return (NULL);
	}
	pthread_create(&waiter, NULL, &end_dinner, caio);
	if (caio->name % 2 == 0)
		usleep(1000);
	pthread_detach(waiter);
	//printf("Caio diz: seja bem vindo filosofo > %i <, sente-se\n", caio->name);
	while(!routine(caio))
		continue ;

	//if (caio->params->death == true && caio->params->exit == false)
	//{
	//	caio->params->exit = true;
		//printf("%ld %i died\n", time_calc(caio->params->start_time), caio->name);
		//printf("In %ld miliseconds %i died\n", time_calc(caio->params->start_time), caio->name);
	//}
	return NULL;
}

static void	init_philosophers(t_philo *philo, t_param *param, int total_philo, int i)
{
	//t_philo *philo;
	//philo->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * total_philo);
	//philo = (t_philo *)malloc(sizeof(t_philo) * total_philo + 64);
	while (i++ < total_philo)
	{
		//printf("CHEGOU O %i NA MESA!\n", i);
		//memset(&philo[i], 0, sizeof(t_philo));
		philo[i].name = i;
		philo[i].fork_right = i;
		philo[i].fork_left = (i + 1) % total_philo;
		//pthread_mutex_init(&philo[i].forks[i], NULL);
		philo[i].params = param;
	}
	i = 0;
	while (i++ < total_philo)
	{
		pthread_create(&philo[i].thread_philo, NULL, &dinner, (void *)&philo[i]);
	}
	i = 0;
	while (i++ < total_philo)
	{
		pthread_join(philo[i].thread_philo, NULL);
	}
	free(philo);
	//printf("philo_name: %i\n", philo[1].name);
	//printf("philo_nbr: %i\n", param->philo_nbr);
	//printf("time_die: %i\n", param->t_todie);
	//printf("time_eat: %i\n", param->t_toeat);
	//printf("time_sleep: %i\n", param->t_tosleep);
}

static int		init_dinner(t_philo *philo, t_param *param)
{
	//printf("CHEGUEI NA MESA!\n");
	//philo = NULL;
	init_philosophers(philo, param, param->philo_nbr, 0);
	//if (philo->satisfied)
	//	printf("Tuco comeu tudo e saiu sem pagar\n");
	return (0);
}

int	main(int argc, char *argv[])
{
	t_param param;
	t_philo *philo;
	int i;

	i = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * (ft_atoi(argv[1])) + 64);
	init_struct(&param, philo);
	ft_memset(&param, 0, sizeof(t_param));
	ft_memset(philo, 0, sizeof(t_philo));
	//param = (void *)malloc(sizeof(t_param));
	//param.start_time = NULL;
	if (validate_args(argc) != 0)
		return(1);
	if (entry_args_check(argc, argv) != 0)
		return(1);
	get_paramm(argv, &param);
	//printf("meals_nbr: %i\n", param.meals_nbr);
	if (init_dinner(philo, &param) != 0)
	{
		printf("rodou init_dinner, vai sair  com a comanda sem pagar, oh la!\n");
		return(1);
	}
	while (i < param.philo_nbr)
	{
		pthread_mutex_destroy(&param.forks[i]);
		i++;
	}
	free(param.forks);
	//while (i++ <= *argv[1])
	//	init_philosophers(i, argv, argc);
	return(0);
}
