#ifndef	PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0

typedef struct s_param
{
	int					philo_nbr;
	int					t_todie;
	int					t_toeat;
	int					t_tosleep;
	int					meals_nbr;
	long int			start_time;
	int						who_dead;
	//bool				exit;
	pthread_mutex_t dead;
	pthread_mutex_t	*forks;
}	t_param;

typedef struct s_philo
{
	int				name;
	long int		last_meal;
	int					meals;
	//bool				death; //bool?
	bool				satisfied; //bool?
	int				times_eat;
	int				fork_left;
	int				fork_right;
	//pthread_mutex_t	*forks;
	pthread_t		thread_philo;
	//struct s_param		*params;
	t_param			*params;
}	t_philo;

/********
** DINNER
*********/
void		*dinner();
void		*end_dinner(void *phi);

/********
** PARSE
*********/
void init_struct(t_param *param, t_philo *philo);
void	get_paramm(char *argv[], t_param *param);

/********
** TIME
*********/
unsigned long int	time_calc(long int start_time);
unsigned long int	phil_clockins(void);
int time_if_died(long int dead_time, long int last_meal);

/********
** UTILS
*********/

int			ft_atoi(const char *str);
int			ft_isdigit(int c);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t count, size_t size);

#endif