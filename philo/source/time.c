#include "../includes/philo.h"

unsigned long int	phil_clockins(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);

	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

unsigned long int time_calc(long int start_time)
{
	long int new_time;

	new_time = phil_clockins();
	//printf("START TIME: %ld\n", start_time);
	//printf("NEW TIME: %ld\n", new_time);
	return (new_time - start_time);
}

int time_if_died(long int dead_time, long int last_meal)
{
	long int new_time;

	new_time = phil_clockins();

	if (new_time - last_meal >= dead_time)
		return (0);
	return (1);
	//return (dead_time - (new_time - last_meal));
}
